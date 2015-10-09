// include LiteSQL's header file and generated header file
#include <iostream>
#include "litesql.hpp"
#include "exampledatabase.hpp"
// provide implementation for Person::sayHello
void example::Person::sayHello() {
    std::cout << "Hi! My name is " << name 
        << " and I am " << age << " years old." << std::endl;
}

void example::user::sayHello() {
    std::cout << "Hi! My name is " << name << std::endl;
}

void example::ThingWithMethods::sayHello(std::string text,int repeat) {
	std::cout << "Hi! I want to say :" << text << std::endl;
}


// no name collisions expected
using namespace litesql;
using namespace example;

int main(int argc, char **argv) {

    try {
    	// using SQLite3 as backend
    	ExampleDatabase db("sqlite3", "database=example.db");
    	// create tables, sequences and indexes
    	db.verbose = true;

    	if (db.needsUpgrade())
    	{
    		db.upgrade();
    	}
    	// start transaction
    	db.begin();

    	// create couple of Person-objects
    	Person jeff(db);
    	DataSource<Person> b = select<Person>(db, Person::Name == "Jeff");
    	if (!b.count()) {
    		jeff.name = "Jeff";
    		jeff.sex = Person::Sex::Male;
    		jeff.age = 32;
    		jeff.aDoubleValue = 0.32;
    		Blob image_jeff("abc",4);
    		jeff.image = image_jeff;
    		// store Jeff to database
    		jeff.update();
    	} else {
    		jeff = b.one();
    	}
    	Person jill(db);
    	auto c = select<Person>(db, Person::Name == "Jill");
    	if (!c.count()) {
    		jill.name = "Jill";
    		jill.sex = Person::Sex::Female;
    		jill.image = Blob("abc", 4);
    		jill.age = 33;
    		jill.update();
    	} else {
    		jill = c.one();
    	}
    	Person jack(db);
    	auto d = select<Person>(db, Person::Name == "Jack");
    	if (!d.count()) {
    		jack.name = "Jack";
    		jack.sex = Person::Sex::Male;
    		jack.update();
    	} else {
    		jack = d.one();
    	}
    	Person jess(db);
    	auto e = select<Person>(db, Person::Name == "Jess");
    	if (!e.count()) {
    		jess.name = "Jess";
    		jess.sex = Person::Sex::Female;
    		jess.update();
    	} else {
    		jess = e.one();
    	}

        // build up relationships between Persons 
    	cout << "Jeff children count: " << jeff.children().get(Person::Name == "Jack").count() << endl;
//    	cout << "His(her) name is: " << jeff.children().get(Person::Name == "Jack").one().name << endl;
    	if (!jeff.children().get(Person::Name == "Jack").count()) {
    		jeff.children().link(jack);
    	}
    	if (!jill.children().get(Person::Name == "Jack").count()) {
    		jill.children().link(jack);
    	}
    	if (!jill.children().get(Person::Name == "Jess").count()) {
    		jill.children().link(jess);
    	}
    	if (!jack.father().get().count()) {
    		jack.father().link(jeff);
    	}
    	if (!jack.mother().get().count()) {
    		jack.mother().link(jill);
    	}
    	if (!jess.mother().get().count()) {
    		jess.mother().link(jill);
    	}
    	if (!jack.siblings().get(Person::Name == "Jill").count()) {
    		jack.siblings().link(jill);
    	}
        // roles (linking examples)


        if (!jeff.roles().get().count()) {
        	Employee jeffRole(db);
        	jeffRole.update();
        	jeff.roles().link(jeffRole);
        	Office office(db);
   	        office.update();
   	        jeffRole.office().link(office);
        }
        if (!jack.roles().get().count()) {
        	Student jackRole(db), jessRole(db);
        	jackRole.update();
        	jessRole.update();
        	jack.roles().link(jackRole);
        	jess.roles().link(jessRole);
        	School school(db);
        	school.update();
        	jackRole.school().link(school);
        	jessRole.school().link(school);
        }
        
        // count Persons
        cout << "There are " << select<Person>(db).count() 
             << " persons." << endl;
	
        // select all Persons and order them by age
        vector<Person> family = select<Person>(db).orderBy(Person::Age).all();
        // show results
        cout << "Reporting family names:" << endl;
        for (Person i: family)
            cout << i.name << endl;
             
        // select intersection of Jeff's and Jill's children and
        // iterate results with cursor
        Cursor<Person> cursor = intersect(jeff.children().get(), 
                                          jill.children().get()).cursor();
        // Jack should say hello
        for (;cursor.rowsLeft();cursor++) 
            (*cursor).sayHello();
        
        // select a non-existing Person
        try {
            select<Person>(db, Person::Id == 100).one();
        } catch (NotFound e) {
            cout << "No Person with id 100" << endl;
        }
        // commit transaction
        db.commit();
        // clean up 
//        db.drop();
    } catch (Except e) {
        cerr << e << endl;
        return -1;
    }
    return 0;
}
