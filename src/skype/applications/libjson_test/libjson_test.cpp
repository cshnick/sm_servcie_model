#include <iostream>
#include <json/json.h>
#include <stdio.h>
constexpr const int chunk = 1024;

/*printing the value corresponding to boolean, double, integer and strings*/
void print_json_value(json_object *jobj){
	enum json_type type;
	printf("type: ",type);
	type = json_object_get_type(jobj); /*Getting the type of the json object*/
	switch (type) {
	case json_type_boolean: printf("json_type_boolean\n");
	printf("value: %s\n", json_object_get_boolean(jobj)? "true": "false");
	break;
	case json_type_double: printf("json_type_double\n");
	printf("          value: %lf\n", json_object_get_double(jobj));
	break;
	case json_type_int: printf("json_type_int\n");
	printf("          value: %d\n", json_object_get_int(jobj));
	break;
	case json_type_string: printf("json_type_string\n");
	printf("          value: %s\n", json_object_get_string(jobj));
	break;
	}
}

void json_parse_array( json_object *jobj, char *key) {
	void json_parse(json_object * jobj); /*Forward Declaration*/
	enum json_type type;

	json_object *jarray = jobj; /*Simply get the array*/
	if(key) {
		jarray = json_object_object_get(jobj, key); /*Getting the array if it is a key value pair*/
	}

	int arraylen = json_object_array_length(jarray); /*Getting the length of the array*/
	printf("Array Length: %d\n",arraylen);
	int i;
	json_object * jvalue;

	for (i=0; i< arraylen; i++){
		jvalue = json_object_array_get_idx(jarray, i); /*Getting the array element at position i*/
		type = json_object_get_type(jvalue);
		if (type == json_type_array) {
			json_parse_array(jvalue, NULL);
		}
		else if (type != json_type_object) {
			printf("value[%d]: ",i);
			print_json_value(jvalue);
		}
		else {
			json_parse(jvalue);
		}
	}
}

/*Parsing the json object*/
void json_parse(json_object * jobj) {
	enum json_type type;
	json_object_object_foreach(jobj, key, val) { /*Passing through every array element*/
		printf("type: ",type);
		type = json_object_get_type(val);
		switch (type) {
		case json_type_boolean:
		case json_type_double:
		case json_type_int:
		case json_type_string: print_json_value(val);
		break;
		case json_type_object: printf("json_type_object\n");
		jobj = json_object_object_get(jobj, key);
		json_parse(jobj);
		break;
		case json_type_array: printf("type: json_type_array, ");
		json_parse_array(jobj, key);
		break;
		}
	}
}

int main() {

	//Reading from existing json object
	FILE *f;
	f = fopen("../../sm_servcie_model/src/skype/applications/libjson_test/test1.json", "rb");
	if (f == NULL) {
		printf("I couldn't open file for reading.\n");
		exit(0);
	}
	long length = -1;
	fseek (f, 0, SEEK_END);
	length = ftell (f);
	enum json_tokener_error jerr;
	fseek (f, 0, SEEK_SET);
	char *buf = (char*)malloc(length);
	if (buf) {
		fread (buf, 1, length, f);
	}
	fclose (f);
	json_tokener *tok = json_tokener_new();
	json_object *jobj = 0;
	printf("JSON string: %s\n", buf);
	do {
		jobj = json_tokener_parse_ex(tok, buf, length);
	} while ((jerr = json_tokener_get_error(tok)) == json_tokener_continue);

	if (jerr != json_tokener_success)
	{
		fprintf(stderr, "Error: %s\n", json_tokener_error_desc(jerr));
		// Handle errors, as appropriate for your application.
	}
	json_parse(jobj);

	free(buf);
	fflush(stdout);

	//Creating new json object
	json_object * jobj_create = json_object_new_object();

	/*Creating a json string*/
	json_object *jstring = json_object_new_string("Joys of Programming");

	/*Creating a json integer*/
	json_object *jint = json_object_new_int(10);

	/*Creating a json boolean*/
	json_object *jboolean = json_object_new_boolean(1);

	/*Creating a json double*/
	json_object *jdouble = json_object_new_double(2.14);

	/*Creating a json array*/
	json_object *jarray = json_object_new_array();

	/*Creating json strings*/
	json_object *jstring1 = json_object_new_string("c");
	json_object *jstring2 = json_object_new_string("c++");
	json_object *jstring3 = json_object_new_string("php");

	/*Adding the above created json strings to the array*/
	json_object_array_add(jarray,jstring1);
	json_object_array_add(jarray,jstring2);
	json_object_array_add(jarray,jstring3);

	/*Form the json object*/
	/*Each of these is like a key value pair*/
	json_object_object_add(jobj_create,"Site Name", jstring);
	json_object_object_add(jobj_create,"Technical blog", jboolean);
	json_object_object_add(jobj_create,"Average posts per day", jdouble);
	json_object_object_add(jobj_create,"Number of posts", jint);
	json_object_object_add(jobj_create,"Categories", jarray);

	/*Now printing the json object*/
	printf ("The json object created: %s\n",json_object_to_json_string(jobj_create));
	fflush(stdout);
	return 0;
}



