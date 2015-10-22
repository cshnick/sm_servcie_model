#include "history_main_db.hpp"
namespace HistoryDB {
using namespace litesql;
ConversationsUsersRelationConvUsers::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : users(ConversationsUsersRelationConvUsers::Users), conversations(ConversationsUsersRelationConvUsers::Conversations) {
    switch(rec.size()) {
    case 2:
        users = rec[1];
    case 1:
        conversations = rec[0];
    }
}
const std::string ConversationsUsersRelationConvUsers::table__("Conversations_Users_ConvUsers");
const litesql::FieldType ConversationsUsersRelationConvUsers::Conversations("Conversations1",A_field_type_integer,table__);
const litesql::FieldType ConversationsUsersRelationConvUsers::Users("Users2",A_field_type_integer,table__);
void ConversationsUsersRelationConvUsers::link(const litesql::Database& db, const HistoryDB::Conversations& o0, const HistoryDB::Users& o1) {
    Record values;
    Split fields;
    fields.push_back(Conversations.name());
    values.push_back(o0.id);
    fields.push_back(Users.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void ConversationsUsersRelationConvUsers::unlink(const litesql::Database& db, const HistoryDB::Conversations& o0, const HistoryDB::Users& o1) {
    db.delete_(table__, (Conversations == o0.id && Users == o1.id));
}
void ConversationsUsersRelationConvUsers::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<ConversationsUsersRelationConvUsers::Row> ConversationsUsersRelationConvUsers::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Conversations.fullName());
    sel.result(Users.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<ConversationsUsersRelationConvUsers::Row>(db, sel);
}
template <> litesql::DataSource<HistoryDB::Conversations> ConversationsUsersRelationConvUsers::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Conversations.fullName());
    sel.where(srcExpr);
    return DataSource<HistoryDB::Conversations>(db, HistoryDB::Conversations::Id.in(sel) && expr);
}
template <> litesql::DataSource<HistoryDB::Users> ConversationsUsersRelationConvUsers::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Users.fullName());
    sel.where(srcExpr);
    return DataSource<HistoryDB::Users>(db, HistoryDB::Users::Id.in(sel) && expr);
}
ConversationsMessagesRelationConvMessages::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : messages(ConversationsMessagesRelationConvMessages::Messages), conversations(ConversationsMessagesRelationConvMessages::Conversations) {
    switch(rec.size()) {
    case 2:
        messages = rec[1];
    case 1:
        conversations = rec[0];
    }
}
const std::string ConversationsMessagesRelationConvMessages::table__("O7c896dc7077d9154b921f4d3004b5");
const litesql::FieldType ConversationsMessagesRelationConvMessages::Conversations("Conversations1",A_field_type_integer,table__);
const litesql::FieldType ConversationsMessagesRelationConvMessages::Messages("Messages2",A_field_type_integer,table__);
void ConversationsMessagesRelationConvMessages::link(const litesql::Database& db, const HistoryDB::Conversations& o0, const HistoryDB::Messages& o1) {
    Record values;
    Split fields;
    fields.push_back(Conversations.name());
    values.push_back(o0.id);
    fields.push_back(Messages.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void ConversationsMessagesRelationConvMessages::unlink(const litesql::Database& db, const HistoryDB::Conversations& o0, const HistoryDB::Messages& o1) {
    db.delete_(table__, (Conversations == o0.id && Messages == o1.id));
}
void ConversationsMessagesRelationConvMessages::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<ConversationsMessagesRelationConvMessages::Row> ConversationsMessagesRelationConvMessages::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Conversations.fullName());
    sel.result(Messages.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<ConversationsMessagesRelationConvMessages::Row>(db, sel);
}
template <> litesql::DataSource<HistoryDB::Conversations> ConversationsMessagesRelationConvMessages::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Conversations.fullName());
    sel.where(srcExpr);
    return DataSource<HistoryDB::Conversations>(db, HistoryDB::Conversations::Id.in(sel) && expr);
}
template <> litesql::DataSource<HistoryDB::Messages> ConversationsMessagesRelationConvMessages::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Messages.fullName());
    sel.where(srcExpr);
    return DataSource<HistoryDB::Messages>(db, HistoryDB::Messages::Id.in(sel) && expr);
}
const litesql::FieldType Chats::Own::Id("id",A_field_type_integer,"Chats");
const std::string Chats::type__("Chats");
const std::string Chats::table__("Chats");
const std::string Chats::sequence__("Chats_seq");
const litesql::FieldType Chats::Id("id",A_field_type_integer,table__);
const litesql::FieldType Chats::Type("type",A_field_type_string,table__);
const litesql::FieldType Chats::Owner("owner",A_field_type_string,table__);
const litesql::FieldType Chats::Name("name",A_field_type_string,table__);
const litesql::FieldType Chats::Creationtime("creationtime",A_field_type_integer,table__);
void Chats::initValues() {
}
void Chats::defaults() {
    id = 0;
    creationtime = 0;
}
Chats::Chats(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), owner(Owner), name(Name), creationtime(Creationtime) {
    defaults();
}
Chats::Chats(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), owner(Owner), name(Name), creationtime(Creationtime) {
    defaults();
    size_t size = (rec.size() > 5) ? 5 : rec.size();
    switch(size) {
    case 5: creationtime = convert<const std::string&, int>(rec[4]);
        creationtime.setModified(false);
    case 4: name = convert<const std::string&, std::string>(rec[3]);
        name.setModified(false);
    case 3: owner = convert<const std::string&, std::string>(rec[2]);
        owner.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Chats::Chats(const Chats& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), owner(obj.owner), name(obj.name), creationtime(obj.creationtime) {
}
const Chats& Chats::operator=(const Chats& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        owner = obj.owner;
        name = obj.name;
        creationtime = obj.creationtime;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string Chats::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(owner.name());
    values.push_back(owner);
    owner.setModified(false);
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fields.push_back(creationtime.name());
    values.push_back(creationtime);
    creationtime.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Chats::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Chats::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, owner);
    updateField(updates, table__, name);
    updateField(updates, table__, creationtime);
}
void Chats::addIDUpdates(Updates& updates) {
}
void Chats::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Owner);
    ftypes.push_back(Name);
    ftypes.push_back(Creationtime);
}
void Chats::delRecord() {
    deleteFromTable(table__, id);
}
void Chats::delRelations() {
}
void Chats::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Chats::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<Chats> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Chats::typeIsCorrect() const {
    return type == type__;
}
std::unique_ptr<Chats> Chats::upcast() const {
    return unique_ptr<Chats>(new Chats(*this));
}
std::unique_ptr<Chats> Chats::upcastCopy() const {
    Chats* np = new Chats(*this);
    np->id = id;
    np->type = type;
    np->owner = owner;
    np->name = name;
    np->creationtime = creationtime;
    np->inDatabase = inDatabase;
    return unique_ptr<Chats>(np);
}
std::ostream & operator<<(std::ostream& os, Chats o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.owner.name() << " = " << o.owner << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << o.creationtime.name() << " = " << o.creationtime << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Conversations::Own::Id("id",A_field_type_integer,"Conversations");
Conversations::UsersHandle::UsersHandle(const Conversations& owner)
         : litesql::RelationHandle<Conversations>(owner) {
}
void Conversations::UsersHandle::link(const Users& o0) {
    ConversationsUsersRelationConvUsers::link(owner->getDatabase(), *owner, o0);
}
void Conversations::UsersHandle::unlink(const Users& o0) {
    ConversationsUsersRelationConvUsers::unlink(owner->getDatabase(), *owner, o0);
}
void Conversations::UsersHandle::del(const litesql::Expr& expr) {
    ConversationsUsersRelationConvUsers::del(owner->getDatabase(), expr && ConversationsUsersRelationConvUsers::Conversations == owner->id);
}
litesql::DataSource<Users> Conversations::UsersHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return ConversationsUsersRelationConvUsers::get<Users>(owner->getDatabase(), expr, (ConversationsUsersRelationConvUsers::Conversations == owner->id) && srcExpr);
}
litesql::DataSource<ConversationsUsersRelationConvUsers::Row> Conversations::UsersHandle::getRows(const litesql::Expr& expr) {
    return ConversationsUsersRelationConvUsers::getRows(owner->getDatabase(), expr && (ConversationsUsersRelationConvUsers::Conversations == owner->id));
}
Conversations::MessagesHandle::MessagesHandle(const Conversations& owner)
         : litesql::RelationHandle<Conversations>(owner) {
}
void Conversations::MessagesHandle::link(const Messages& o0) {
    ConversationsMessagesRelationConvMessages::link(owner->getDatabase(), *owner, o0);
}
void Conversations::MessagesHandle::unlink(const Messages& o0) {
    ConversationsMessagesRelationConvMessages::unlink(owner->getDatabase(), *owner, o0);
}
void Conversations::MessagesHandle::del(const litesql::Expr& expr) {
    ConversationsMessagesRelationConvMessages::del(owner->getDatabase(), expr && ConversationsMessagesRelationConvMessages::Conversations == owner->id);
}
litesql::DataSource<Messages> Conversations::MessagesHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return ConversationsMessagesRelationConvMessages::get<Messages>(owner->getDatabase(), expr, (ConversationsMessagesRelationConvMessages::Conversations == owner->id) && srcExpr);
}
litesql::DataSource<ConversationsMessagesRelationConvMessages::Row> Conversations::MessagesHandle::getRows(const litesql::Expr& expr) {
    return ConversationsMessagesRelationConvMessages::getRows(owner->getDatabase(), expr && (ConversationsMessagesRelationConvMessages::Conversations == owner->id));
}
const std::string Conversations::type__("Conversations");
const std::string Conversations::table__("Conversations");
const std::string Conversations::sequence__("Conversations_seq");
const litesql::FieldType Conversations::Id("id",A_field_type_integer,table__);
const litesql::FieldType Conversations::Type("type",A_field_type_string,table__);
const litesql::FieldType Conversations::Friendlyname("friendlyname",A_field_type_string,table__);
void Conversations::initValues() {
}
void Conversations::defaults() {
    id = 0;
}
Conversations::Conversations(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), friendlyname(Friendlyname) {
    defaults();
}
Conversations::Conversations(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), friendlyname(Friendlyname) {
    defaults();
    size_t size = (rec.size() > 3) ? 3 : rec.size();
    switch(size) {
    case 3: friendlyname = convert<const std::string&, std::string>(rec[2]);
        friendlyname.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Conversations::Conversations(const Conversations& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), friendlyname(obj.friendlyname) {
}
const Conversations& Conversations::operator=(const Conversations& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        friendlyname = obj.friendlyname;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
Conversations::UsersHandle Conversations::users() {
    return Conversations::UsersHandle(*this);
}
Conversations::MessagesHandle Conversations::messages() {
    return Conversations::MessagesHandle(*this);
}
std::string Conversations::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(friendlyname.name());
    values.push_back(friendlyname);
    friendlyname.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Conversations::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Conversations::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, friendlyname);
}
void Conversations::addIDUpdates(Updates& updates) {
}
void Conversations::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Friendlyname);
}
void Conversations::delRecord() {
    deleteFromTable(table__, id);
}
void Conversations::delRelations() {
    ConversationsUsersRelationConvUsers::del(*db, (ConversationsUsersRelationConvUsers::Conversations == id));
    ConversationsMessagesRelationConvMessages::del(*db, (ConversationsMessagesRelationConvMessages::Conversations == id));
}
void Conversations::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Conversations::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<Conversations> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Conversations::typeIsCorrect() const {
    return type == type__;
}
std::unique_ptr<Conversations> Conversations::upcast() const {
    return unique_ptr<Conversations>(new Conversations(*this));
}
std::unique_ptr<Conversations> Conversations::upcastCopy() const {
    Conversations* np = new Conversations(*this);
    np->id = id;
    np->type = type;
    np->friendlyname = friendlyname;
    np->inDatabase = inDatabase;
    return unique_ptr<Conversations>(np);
}
std::ostream & operator<<(std::ostream& os, Conversations o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.friendlyname.name() << " = " << o.friendlyname << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType ChatUsers::Own::Id("id",A_field_type_integer,"ChatUsers");
const std::string ChatUsers::type__("ChatUsers");
const std::string ChatUsers::table__("ChatUsers");
const std::string ChatUsers::sequence__("ChatUsers_seq");
const litesql::FieldType ChatUsers::Id("id",A_field_type_integer,table__);
const litesql::FieldType ChatUsers::Type("type",A_field_type_string,table__);
const litesql::FieldType ChatUsers::User_id("user_id",A_field_type_integer,table__);
const litesql::FieldType ChatUsers::Chat_id("chat_id",A_field_type_integer,table__);
void ChatUsers::initValues() {
}
void ChatUsers::defaults() {
    id = 0;
    user_id = 0;
    chat_id = 0;
}
ChatUsers::ChatUsers(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), user_id(User_id), chat_id(Chat_id) {
    defaults();
}
ChatUsers::ChatUsers(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), user_id(User_id), chat_id(Chat_id) {
    defaults();
    size_t size = (rec.size() > 4) ? 4 : rec.size();
    switch(size) {
    case 4: chat_id = convert<const std::string&, int>(rec[3]);
        chat_id.setModified(false);
    case 3: user_id = convert<const std::string&, int>(rec[2]);
        user_id.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
ChatUsers::ChatUsers(const ChatUsers& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), user_id(obj.user_id), chat_id(obj.chat_id) {
}
const ChatUsers& ChatUsers::operator=(const ChatUsers& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        user_id = obj.user_id;
        chat_id = obj.chat_id;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string ChatUsers::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(user_id.name());
    values.push_back(user_id);
    user_id.setModified(false);
    fields.push_back(chat_id.name());
    values.push_back(chat_id);
    chat_id.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void ChatUsers::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void ChatUsers::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, user_id);
    updateField(updates, table__, chat_id);
}
void ChatUsers::addIDUpdates(Updates& updates) {
}
void ChatUsers::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(User_id);
    ftypes.push_back(Chat_id);
}
void ChatUsers::delRecord() {
    deleteFromTable(table__, id);
}
void ChatUsers::delRelations() {
}
void ChatUsers::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void ChatUsers::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<ChatUsers> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool ChatUsers::typeIsCorrect() const {
    return type == type__;
}
std::unique_ptr<ChatUsers> ChatUsers::upcast() const {
    return unique_ptr<ChatUsers>(new ChatUsers(*this));
}
std::unique_ptr<ChatUsers> ChatUsers::upcastCopy() const {
    ChatUsers* np = new ChatUsers(*this);
    np->id = id;
    np->type = type;
    np->user_id = user_id;
    np->chat_id = chat_id;
    np->inDatabase = inDatabase;
    return unique_ptr<ChatUsers>(np);
}
std::ostream & operator<<(std::ostream& os, ChatUsers o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.user_id.name() << " = " << o.user_id << std::endl;
    os << o.chat_id.name() << " = " << o.chat_id << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType info::Own::Id("id",A_field_type_integer,"info");
const std::string info::type__("info");
const std::string info::table__("info");
const std::string info::sequence__("info_seq");
const litesql::FieldType info::Id("id",A_field_type_integer,table__);
const litesql::FieldType info::Type("type",A_field_type_string,table__);
const litesql::FieldType info::Dbversion("dbversion",A_field_type_integer,table__);
void info::initValues() {
}
void info::defaults() {
    id = 0;
    dbversion = 0;
}
info::info(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), dbversion(Dbversion) {
    defaults();
}
info::info(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), dbversion(Dbversion) {
    defaults();
    size_t size = (rec.size() > 3) ? 3 : rec.size();
    switch(size) {
    case 3: dbversion = convert<const std::string&, int>(rec[2]);
        dbversion.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
info::info(const info& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), dbversion(obj.dbversion) {
}
const info& info::operator=(const info& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        dbversion = obj.dbversion;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string info::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(dbversion.name());
    values.push_back(dbversion);
    dbversion.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void info::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void info::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, dbversion);
}
void info::addIDUpdates(Updates& updates) {
}
void info::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Dbversion);
}
void info::delRecord() {
    deleteFromTable(table__, id);
}
void info::delRelations() {
}
void info::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void info::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<info> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool info::typeIsCorrect() const {
    return type == type__;
}
std::unique_ptr<info> info::upcast() const {
    return unique_ptr<info>(new info(*this));
}
std::unique_ptr<info> info::upcastCopy() const {
    info* np = new info(*this);
    np->id = id;
    np->type = type;
    np->dbversion = dbversion;
    np->inDatabase = inDatabase;
    return unique_ptr<info>(np);
}
std::ostream & operator<<(std::ostream& os, info o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.dbversion.name() << " = " << o.dbversion << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Messages::Own::Id("id",A_field_type_integer,"Messages");
Messages::ConversationHandle::ConversationHandle(const Messages& owner)
         : litesql::RelationHandle<Messages>(owner) {
}
void Messages::ConversationHandle::link(const Conversations& o0) {
    ConversationsMessagesRelationConvMessages::link(owner->getDatabase(), o0, *owner);
}
void Messages::ConversationHandle::unlink(const Conversations& o0) {
    ConversationsMessagesRelationConvMessages::unlink(owner->getDatabase(), o0, *owner);
}
void Messages::ConversationHandle::del(const litesql::Expr& expr) {
    ConversationsMessagesRelationConvMessages::del(owner->getDatabase(), expr && ConversationsMessagesRelationConvMessages::Messages == owner->id);
}
litesql::DataSource<Conversations> Messages::ConversationHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return ConversationsMessagesRelationConvMessages::get<Conversations>(owner->getDatabase(), expr, (ConversationsMessagesRelationConvMessages::Messages == owner->id) && srcExpr);
}
litesql::DataSource<ConversationsMessagesRelationConvMessages::Row> Messages::ConversationHandle::getRows(const litesql::Expr& expr) {
    return ConversationsMessagesRelationConvMessages::getRows(owner->getDatabase(), expr && (ConversationsMessagesRelationConvMessages::Messages == owner->id));
}
const std::string Messages::type__("Messages");
const std::string Messages::table__("Messages");
const std::string Messages::sequence__("Messages_seq");
const litesql::FieldType Messages::Id("id",A_field_type_integer,table__);
const litesql::FieldType Messages::Type("type",A_field_type_string,table__);
const litesql::FieldType Messages::Body("body",A_field_type_string,table__);
const litesql::FieldType Messages::Chat_id("chat_id",A_field_type_integer,table__);
const litesql::FieldType Messages::Timestamp("timestamp",A_field_type_integer,table__);
const litesql::FieldType Messages::Sender_id("sender_id",A_field_type_integer,table__);
const litesql::FieldType Messages::Skype_id("skype_id",A_field_type_integer,table__);
const litesql::FieldType Messages::Skype_timestamp("skype_timestamp",A_field_type_integer,table__);
void Messages::initValues() {
}
void Messages::defaults() {
    id = 0;
    chat_id = 0;
    timestamp = 0;
    sender_id = 0;
    skype_id = 0;
    skype_timestamp = 0;
}
Messages::Messages(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), body(Body), chat_id(Chat_id), timestamp(Timestamp), sender_id(Sender_id), skype_id(Skype_id), skype_timestamp(Skype_timestamp) {
    defaults();
}
Messages::Messages(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), body(Body), chat_id(Chat_id), timestamp(Timestamp), sender_id(Sender_id), skype_id(Skype_id), skype_timestamp(Skype_timestamp) {
    defaults();
    size_t size = (rec.size() > 8) ? 8 : rec.size();
    switch(size) {
    case 8: skype_timestamp = convert<const std::string&, int>(rec[7]);
        skype_timestamp.setModified(false);
    case 7: skype_id = convert<const std::string&, int>(rec[6]);
        skype_id.setModified(false);
    case 6: sender_id = convert<const std::string&, int>(rec[5]);
        sender_id.setModified(false);
    case 5: timestamp = convert<const std::string&, int>(rec[4]);
        timestamp.setModified(false);
    case 4: chat_id = convert<const std::string&, int>(rec[3]);
        chat_id.setModified(false);
    case 3: body = convert<const std::string&, std::string>(rec[2]);
        body.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Messages::Messages(const Messages& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), body(obj.body), chat_id(obj.chat_id), timestamp(obj.timestamp), sender_id(obj.sender_id), skype_id(obj.skype_id), skype_timestamp(obj.skype_timestamp) {
}
const Messages& Messages::operator=(const Messages& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        body = obj.body;
        chat_id = obj.chat_id;
        timestamp = obj.timestamp;
        sender_id = obj.sender_id;
        skype_id = obj.skype_id;
        skype_timestamp = obj.skype_timestamp;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
Messages::ConversationHandle Messages::conversation() {
    return Messages::ConversationHandle(*this);
}
std::string Messages::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(body.name());
    values.push_back(body);
    body.setModified(false);
    fields.push_back(chat_id.name());
    values.push_back(chat_id);
    chat_id.setModified(false);
    fields.push_back(timestamp.name());
    values.push_back(timestamp);
    timestamp.setModified(false);
    fields.push_back(sender_id.name());
    values.push_back(sender_id);
    sender_id.setModified(false);
    fields.push_back(skype_id.name());
    values.push_back(skype_id);
    skype_id.setModified(false);
    fields.push_back(skype_timestamp.name());
    values.push_back(skype_timestamp);
    skype_timestamp.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Messages::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Messages::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, body);
    updateField(updates, table__, chat_id);
    updateField(updates, table__, timestamp);
    updateField(updates, table__, sender_id);
    updateField(updates, table__, skype_id);
    updateField(updates, table__, skype_timestamp);
}
void Messages::addIDUpdates(Updates& updates) {
}
void Messages::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Body);
    ftypes.push_back(Chat_id);
    ftypes.push_back(Timestamp);
    ftypes.push_back(Sender_id);
    ftypes.push_back(Skype_id);
    ftypes.push_back(Skype_timestamp);
}
void Messages::delRecord() {
    deleteFromTable(table__, id);
}
void Messages::delRelations() {
    ConversationsMessagesRelationConvMessages::del(*db, (ConversationsMessagesRelationConvMessages::Messages == id));
}
void Messages::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Messages::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<Messages> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Messages::typeIsCorrect() const {
    return type == type__;
}
std::unique_ptr<Messages> Messages::upcast() const {
    return unique_ptr<Messages>(new Messages(*this));
}
std::unique_ptr<Messages> Messages::upcastCopy() const {
    Messages* np = new Messages(*this);
    np->id = id;
    np->type = type;
    np->body = body;
    np->chat_id = chat_id;
    np->timestamp = timestamp;
    np->sender_id = sender_id;
    np->skype_id = skype_id;
    np->skype_timestamp = skype_timestamp;
    np->inDatabase = inDatabase;
    return unique_ptr<Messages>(np);
}
std::ostream & operator<<(std::ostream& os, Messages o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.body.name() << " = " << o.body << std::endl;
    os << o.chat_id.name() << " = " << o.chat_id << std::endl;
    os << o.timestamp.name() << " = " << o.timestamp << std::endl;
    os << o.sender_id.name() << " = " << o.sender_id << std::endl;
    os << o.skype_id.name() << " = " << o.skype_id << std::endl;
    os << o.skype_timestamp.name() << " = " << o.skype_timestamp << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Users::Own::Id("id",A_field_type_integer,"Users");
Users::ConversationHandle::ConversationHandle(const Users& owner)
         : litesql::RelationHandle<Users>(owner) {
}
void Users::ConversationHandle::link(const Conversations& o0) {
    ConversationsUsersRelationConvUsers::link(owner->getDatabase(), o0, *owner);
}
void Users::ConversationHandle::unlink(const Conversations& o0) {
    ConversationsUsersRelationConvUsers::unlink(owner->getDatabase(), o0, *owner);
}
void Users::ConversationHandle::del(const litesql::Expr& expr) {
    ConversationsUsersRelationConvUsers::del(owner->getDatabase(), expr && ConversationsUsersRelationConvUsers::Users == owner->id);
}
litesql::DataSource<Conversations> Users::ConversationHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return ConversationsUsersRelationConvUsers::get<Conversations>(owner->getDatabase(), expr, (ConversationsUsersRelationConvUsers::Users == owner->id) && srcExpr);
}
litesql::DataSource<ConversationsUsersRelationConvUsers::Row> Users::ConversationHandle::getRows(const litesql::Expr& expr) {
    return ConversationsUsersRelationConvUsers::getRows(owner->getDatabase(), expr && (ConversationsUsersRelationConvUsers::Users == owner->id));
}
const std::string Users::type__("Users");
const std::string Users::table__("Users");
const std::string Users::sequence__("Users_seq");
const litesql::FieldType Users::Id("id",A_field_type_integer,table__);
const litesql::FieldType Users::Type("type",A_field_type_string,table__);
const litesql::FieldType Users::Displayname("displayname",A_field_type_string,table__);
const litesql::FieldType Users::Name("name",A_field_type_string,table__);
const litesql::FieldType Users::Lastmessagetime("lastmessagetime",A_field_type_integer,table__);
void Users::initValues() {
}
void Users::defaults() {
    id = 0;
    lastmessagetime = 0;
}
Users::Users(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), displayname(Displayname), name(Name), lastmessagetime(Lastmessagetime) {
    defaults();
}
Users::Users(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), displayname(Displayname), name(Name), lastmessagetime(Lastmessagetime) {
    defaults();
    size_t size = (rec.size() > 5) ? 5 : rec.size();
    switch(size) {
    case 5: lastmessagetime = convert<const std::string&, int>(rec[4]);
        lastmessagetime.setModified(false);
    case 4: name = convert<const std::string&, std::string>(rec[3]);
        name.setModified(false);
    case 3: displayname = convert<const std::string&, std::string>(rec[2]);
        displayname.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Users::Users(const Users& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), displayname(obj.displayname), name(obj.name), lastmessagetime(obj.lastmessagetime) {
}
const Users& Users::operator=(const Users& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        displayname = obj.displayname;
        name = obj.name;
        lastmessagetime = obj.lastmessagetime;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
Users::ConversationHandle Users::conversation() {
    return Users::ConversationHandle(*this);
}
std::string Users::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(displayname.name());
    values.push_back(displayname);
    displayname.setModified(false);
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fields.push_back(lastmessagetime.name());
    values.push_back(lastmessagetime);
    lastmessagetime.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Users::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Users::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, displayname);
    updateField(updates, table__, name);
    updateField(updates, table__, lastmessagetime);
}
void Users::addIDUpdates(Updates& updates) {
}
void Users::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Displayname);
    ftypes.push_back(Name);
    ftypes.push_back(Lastmessagetime);
}
void Users::delRecord() {
    deleteFromTable(table__, id);
}
void Users::delRelations() {
    ConversationsUsersRelationConvUsers::del(*db, (ConversationsUsersRelationConvUsers::Users == id));
}
void Users::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Users::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<Users> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Users::typeIsCorrect() const {
    return type == type__;
}
std::unique_ptr<Users> Users::upcast() const {
    return unique_ptr<Users>(new Users(*this));
}
std::unique_ptr<Users> Users::upcastCopy() const {
    Users* np = new Users(*this);
    np->id = id;
    np->type = type;
    np->displayname = displayname;
    np->name = name;
    np->lastmessagetime = lastmessagetime;
    np->inDatabase = inDatabase;
    return unique_ptr<Users>(np);
}
std::ostream & operator<<(std::ostream& os, Users o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.displayname.name() << " = " << o.displayname << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << o.lastmessagetime.name() << " = " << o.lastmessagetime << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
history::history(std::string backendType, std::string connInfo)
     : litesql::Database(backendType, connInfo) {
    initialize();
}
std::vector<litesql::Database::SchemaItem> history::getSchema() const {
    vector<Database::SchemaItem> res;
    string TEXT = backend->getSQLType(A_field_type_string);
    string rowIdType = backend->getRowIDType();
    res.push_back(Database::SchemaItem("schema_","table","CREATE TABLE schema_ (name_ "+TEXT+", type_ "+TEXT+", sql_ "+TEXT+")"));
    if (backend->supportsSequences()) {
        res.push_back(Database::SchemaItem("Chats_seq","sequence",backend->getCreateSequenceSQL("Chats_seq")));
        res.push_back(Database::SchemaItem("Conversations_seq","sequence",backend->getCreateSequenceSQL("Conversations_seq")));
        res.push_back(Database::SchemaItem("ChatUsers_seq","sequence",backend->getCreateSequenceSQL("ChatUsers_seq")));
        res.push_back(Database::SchemaItem("info_seq","sequence",backend->getCreateSequenceSQL("info_seq")));
        res.push_back(Database::SchemaItem("Messages_seq","sequence",backend->getCreateSequenceSQL("Messages_seq")));
        res.push_back(Database::SchemaItem("Users_seq","sequence",backend->getCreateSequenceSQL("Users_seq")));
    }
    res.push_back(Database::SchemaItem("Chats","table","CREATE TABLE Chats (id " + rowIdType + ",type " + backend->getSQLType(A_field_type_string,"") + "" +",owner " + backend->getSQLType(A_field_type_string,"") + "" +",name " + backend->getSQLType(A_field_type_string,"") + "" +",creationtime " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("Conversations","table","CREATE TABLE Conversations (id " + rowIdType + ",type " + backend->getSQLType(A_field_type_string,"") + "" +",friendlyname " + backend->getSQLType(A_field_type_string,"") + "" +")"));
    res.push_back(Database::SchemaItem("ChatUsers","table","CREATE TABLE ChatUsers (id " + rowIdType + ",type " + backend->getSQLType(A_field_type_string,"") + "" +",user_id " + backend->getSQLType(A_field_type_integer,"") + "" +",chat_id " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("info","table","CREATE TABLE info (id " + rowIdType + ",type " + backend->getSQLType(A_field_type_string,"") + "" +",dbversion " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("Messages","table","CREATE TABLE Messages (id " + rowIdType + ",type " + backend->getSQLType(A_field_type_string,"") + "" +",body " + backend->getSQLType(A_field_type_string,"") + "" +",chat_id " + backend->getSQLType(A_field_type_integer,"") + "" +",timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +",sender_id " + backend->getSQLType(A_field_type_integer,"") + "" +",skype_id " + backend->getSQLType(A_field_type_integer,"") + "" +",skype_timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("Users","table","CREATE TABLE Users (id " + rowIdType + ",type " + backend->getSQLType(A_field_type_string,"") + "" +",displayname " + backend->getSQLType(A_field_type_string,"") + "" +",name " + backend->getSQLType(A_field_type_string,"") + "" +",lastmessagetime " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("Conversations_Users_ConvUsers","table","CREATE TABLE Conversations_Users_ConvUsers (Conversations1 " + backend->getSQLType(A_field_type_integer,"") + "" +",Users2 " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("O7c896dc7077d9154b921f4d3004b5","table","CREATE TABLE O7c896dc7077d9154b921f4d3004b5 (Conversations1 " + backend->getSQLType(A_field_type_integer,"") + "" +",Messages2 " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("Chatsididx","index","CREATE INDEX Chatsididx ON Chats (id)"));
    res.push_back(Database::SchemaItem("Conversationsididx","index","CREATE INDEX Conversationsididx ON Conversations (id)"));
    res.push_back(Database::SchemaItem("ChatUsersididx","index","CREATE INDEX ChatUsersididx ON ChatUsers (id)"));
    res.push_back(Database::SchemaItem("infoididx","index","CREATE INDEX infoididx ON info (id)"));
    res.push_back(Database::SchemaItem("Messagesididx","index","CREATE INDEX Messagesididx ON Messages (id)"));
    res.push_back(Database::SchemaItem("Usersididx","index","CREATE INDEX Usersididx ON Users (id)"));
    res.push_back(Database::SchemaItem("Oe612685034171ce5288e89b71f6ca","index","CREATE INDEX Oe612685034171ce5288e89b71f6ca ON Conversations_Users_ConvUsers (Conversations1)"));
    res.push_back(Database::SchemaItem("Oc5dbfb5ff83170a0427faaf32d429","index","CREATE INDEX Oc5dbfb5ff83170a0427faaf32d429 ON Conversations_Users_ConvUsers (Users2)"));
    res.push_back(Database::SchemaItem("O2b78447bad7217d76077f2972704c","index","CREATE INDEX O2b78447bad7217d76077f2972704c ON Conversations_Users_ConvUsers (Conversations1,Users2)"));
    res.push_back(Database::SchemaItem("O3bb020e5d1dd8015cd86e881b40de","index","CREATE INDEX O3bb020e5d1dd8015cd86e881b40de ON O7c896dc7077d9154b921f4d3004b5 (Conversations1)"));
    res.push_back(Database::SchemaItem("O2332cfff1ff0db8f9a52f200958ae","index","CREATE INDEX O2332cfff1ff0db8f9a52f200958ae ON O7c896dc7077d9154b921f4d3004b5 (Messages2)"));
    res.push_back(Database::SchemaItem("O7a00bd74aa795d0f4a29b46d7229a","index","CREATE INDEX O7a00bd74aa795d0f4a29b46d7229a ON O7c896dc7077d9154b921f4d3004b5 (Conversations1,Messages2)"));
    return res;
}
void history::initialize() {
    static bool initialized = false;
    if (initialized)
        return;
    initialized = true;
}
}
