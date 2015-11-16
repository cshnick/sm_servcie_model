#include "skype_main_db.hpp"
namespace SkypeDB {
using namespace litesql;
const litesql::FieldType Accounts::Own::Id("id",A_field_type_integer,"Accounts");
const std::string Accounts::type__("Accounts");
const std::string Accounts::table__("Accounts");
const std::string Accounts::sequence__("Accounts_seq");
const litesql::FieldType Accounts::Id("id",A_field_type_integer,table__);
const litesql::FieldType Accounts::Skypename("skypename",A_field_type_string,table__);
const litesql::FieldType Accounts::Fullname("fullname",A_field_type_string,table__);
void Accounts::initValues() {
}
void Accounts::defaults() {
    id = 0;
}
Accounts::Accounts(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), skypename(Skypename), fullname(Fullname) {
    defaults();
}
Accounts::Accounts(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), skypename(Skypename), fullname(Fullname) {
    defaults();
    size_t size = (rec.size() > 3) ? 3 : rec.size();
    switch(size) {
    case 3: fullname = convert<const std::string&, std::string>(rec[2]);
        fullname.setModified(false);
    case 2: skypename = convert<const std::string&, std::string>(rec[1]);
        skypename.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Accounts::Accounts(const Accounts& obj)
     : litesql::Persistent(obj), id(obj.id), skypename(obj.skypename), fullname(obj.fullname) {
}
const Accounts& Accounts::operator=(const Accounts& obj) {
    if (this != &obj) {
        id = obj.id;
        skypename = obj.skypename;
        fullname = obj.fullname;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string Accounts::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(skypename.name());
    values.push_back(skypename);
    skypename.setModified(false);
    fields.push_back(fullname.name());
    values.push_back(fullname);
    fullname.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Accounts::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    //Type processing disabled
    //type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Accounts::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, skypename);
    updateField(updates, table__, fullname);
}
void Accounts::addIDUpdates(Updates& updates) {
}
void Accounts::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Skypename);
    ftypes.push_back(Fullname);
}
void Accounts::delRecord() {
    deleteFromTable(table__, id);
}
void Accounts::delRelations() {
}
void Accounts::update() {
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
void Accounts::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<Accounts> p(upcastCopy());
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
bool Accounts::typeIsCorrect() const {
    return true;
}
std::unique_ptr<Accounts> Accounts::upcast() const {
    return unique_ptr<Accounts>(new Accounts(*this));
}
std::unique_ptr<Accounts> Accounts::upcastCopy() const {
    Accounts* np = new Accounts(*this);
    np->id = id;
    np->skypename = skypename;
    np->fullname = fullname;
    np->inDatabase = inDatabase;
    return unique_ptr<Accounts>(np);
}
std::ostream & operator<<(std::ostream& os, Accounts o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.skypename.name() << " = " << o.skypename << std::endl;
    os << o.fullname.name() << " = " << o.fullname << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Messages::Own::Id("id",A_field_type_integer,"Messages");
const std::string Messages::type__("Messages");
const std::string Messages::table__("Messages");
const std::string Messages::sequence__("Messages_seq");
const litesql::FieldType Messages::Id("id",A_field_type_integer,table__);
const litesql::FieldType Messages::Is_permanent("is_permanent",A_field_type_integer,table__);
const litesql::FieldType Messages::Convo_id("convo_id",A_field_type_integer,table__);
const litesql::FieldType Messages::Chatname("chatname",A_field_type_string,table__);
const litesql::FieldType Messages::Author("author",A_field_type_string,table__);
const litesql::FieldType Messages::From_dispname("from_dispname",A_field_type_string,table__);
const litesql::FieldType Messages::Author_was_live("author_was_live",A_field_type_integer,table__);
const litesql::FieldType Messages::Guid("guid",A_field_type_blob,table__);
const litesql::FieldType Messages::Dialog_partner("dialog_partner",A_field_type_string,table__);
const litesql::FieldType Messages::Timestamp("timestamp",A_field_type_integer,table__);
const litesql::FieldType Messages::Sending_status("sending_status",A_field_type_integer,table__);
const litesql::FieldType Messages::Consumption_status("consumption_status",A_field_type_integer,table__);
const litesql::FieldType Messages::Edited_by("edited_by",A_field_type_string,table__);
const litesql::FieldType Messages::Edited_timestamp("edited_timestamp",A_field_type_integer,table__);
const litesql::FieldType Messages::Param_key("param_key",A_field_type_integer,table__);
const litesql::FieldType Messages::Param_value("param_value",A_field_type_integer,table__);
const litesql::FieldType Messages::Body_xml("body_xml",A_field_type_string,table__);
const litesql::FieldType Messages::Identities("identities",A_field_type_string,table__);
const litesql::FieldType Messages::Reason("reason",A_field_type_string,table__);
const litesql::FieldType Messages::Leavereason("leavereason",A_field_type_integer,table__);
const litesql::FieldType Messages::Participant_count("participant_count",A_field_type_integer,table__);
const litesql::FieldType Messages::Error_code("error_code",A_field_type_integer,table__);
const litesql::FieldType Messages::Chatmsg_type("chatmsg_type",A_field_type_integer,table__);
const litesql::FieldType Messages::Chatmsg_status("chatmsg_status",A_field_type_integer,table__);
const litesql::FieldType Messages::Body_is_rawxml("body_is_rawxml",A_field_type_integer,table__);
const litesql::FieldType Messages::Oldoptions("oldoptions",A_field_type_integer,table__);
const litesql::FieldType Messages::Newoptions("newoptions",A_field_type_integer,table__);
const litesql::FieldType Messages::Newrole("newrole",A_field_type_integer,table__);
const litesql::FieldType Messages::Pk_id("pk_id",A_field_type_integer,table__);
const litesql::FieldType Messages::Crc("crc",A_field_type_integer,table__);
const litesql::FieldType Messages::Remote_id("remote_id",A_field_type_integer,table__);
const litesql::FieldType Messages::Call_guid("call_guid",A_field_type_string,table__);
void Messages::initValues() {
}
void Messages::defaults() {
    id = 0;
    is_permanent = 0;
    convo_id = 0;
    author_was_live = 0;
    guid = Blob();
    timestamp = 0;
    sending_status = 0;
    consumption_status = 0;
    edited_timestamp = 0;
    param_key = 0;
    param_value = 0;
    leavereason = 0;
    participant_count = 0;
    error_code = 0;
    chatmsg_type = 0;
    chatmsg_status = 0;
    body_is_rawxml = 0;
    oldoptions = 0;
    newoptions = 0;
    newrole = 0;
    pk_id = 0;
    crc = 0;
    remote_id = 0;
}
Messages::Messages(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), is_permanent(Is_permanent), convo_id(Convo_id), chatname(Chatname), author(Author), from_dispname(From_dispname), author_was_live(Author_was_live), guid(Guid), dialog_partner(Dialog_partner), timestamp(Timestamp), sending_status(Sending_status), consumption_status(Consumption_status), edited_by(Edited_by), edited_timestamp(Edited_timestamp), param_key(Param_key), param_value(Param_value), body_xml(Body_xml), identities(Identities), reason(Reason), leavereason(Leavereason), participant_count(Participant_count), error_code(Error_code), chatmsg_type(Chatmsg_type), chatmsg_status(Chatmsg_status), body_is_rawxml(Body_is_rawxml), oldoptions(Oldoptions), newoptions(Newoptions), newrole(Newrole), pk_id(Pk_id), crc(Crc), remote_id(Remote_id), call_guid(Call_guid) {
    defaults();
}
Messages::Messages(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), is_permanent(Is_permanent), convo_id(Convo_id), chatname(Chatname), author(Author), from_dispname(From_dispname), author_was_live(Author_was_live), guid(Guid), dialog_partner(Dialog_partner), timestamp(Timestamp), sending_status(Sending_status), consumption_status(Consumption_status), edited_by(Edited_by), edited_timestamp(Edited_timestamp), param_key(Param_key), param_value(Param_value), body_xml(Body_xml), identities(Identities), reason(Reason), leavereason(Leavereason), participant_count(Participant_count), error_code(Error_code), chatmsg_type(Chatmsg_type), chatmsg_status(Chatmsg_status), body_is_rawxml(Body_is_rawxml), oldoptions(Oldoptions), newoptions(Newoptions), newrole(Newrole), pk_id(Pk_id), crc(Crc), remote_id(Remote_id), call_guid(Call_guid) {
    defaults();
    size_t size = (rec.size() > 32) ? 32 : rec.size();
    switch(size) {
    case 32: call_guid = convert<const std::string&, std::string>(rec[31]);
        call_guid.setModified(false);
    case 31: remote_id = convert<const std::string&, int>(rec[30]);
        remote_id.setModified(false);
    case 30: crc = convert<const std::string&, int>(rec[29]);
        crc.setModified(false);
    case 29: pk_id = convert<const std::string&, int>(rec[28]);
        pk_id.setModified(false);
    case 28: newrole = convert<const std::string&, int>(rec[27]);
        newrole.setModified(false);
    case 27: newoptions = convert<const std::string&, int>(rec[26]);
        newoptions.setModified(false);
    case 26: oldoptions = convert<const std::string&, int>(rec[25]);
        oldoptions.setModified(false);
    case 25: body_is_rawxml = convert<const std::string&, int>(rec[24]);
        body_is_rawxml.setModified(false);
    case 24: chatmsg_status = convert<const std::string&, int>(rec[23]);
        chatmsg_status.setModified(false);
    case 23: chatmsg_type = convert<const std::string&, int>(rec[22]);
        chatmsg_type.setModified(false);
    case 22: error_code = convert<const std::string&, int>(rec[21]);
        error_code.setModified(false);
    case 21: participant_count = convert<const std::string&, int>(rec[20]);
        participant_count.setModified(false);
    case 20: leavereason = convert<const std::string&, int>(rec[19]);
        leavereason.setModified(false);
    case 19: reason = convert<const std::string&, std::string>(rec[18]);
        reason.setModified(false);
    case 18: identities = convert<const std::string&, std::string>(rec[17]);
        identities.setModified(false);
    case 17: body_xml = convert<const std::string&, std::string>(rec[16]);
        body_xml.setModified(false);
    case 16: param_value = convert<const std::string&, int>(rec[15]);
        param_value.setModified(false);
    case 15: param_key = convert<const std::string&, int>(rec[14]);
        param_key.setModified(false);
    case 14: edited_timestamp = convert<const std::string&, int>(rec[13]);
        edited_timestamp.setModified(false);
    case 13: edited_by = convert<const std::string&, std::string>(rec[12]);
        edited_by.setModified(false);
    case 12: consumption_status = convert<const std::string&, int>(rec[11]);
        consumption_status.setModified(false);
    case 11: sending_status = convert<const std::string&, int>(rec[10]);
        sending_status.setModified(false);
    case 10: timestamp = convert<const std::string&, int>(rec[9]);
        timestamp.setModified(false);
    case 9: dialog_partner = convert<const std::string&, std::string>(rec[8]);
        dialog_partner.setModified(false);
    case 8: guid = convert<const std::string&, litesql::Blob>(rec[7]);
        guid.setModified(false);
    case 7: author_was_live = convert<const std::string&, int>(rec[6]);
        author_was_live.setModified(false);
    case 6: from_dispname = convert<const std::string&, std::string>(rec[5]);
        from_dispname.setModified(false);
    case 5: author = convert<const std::string&, std::string>(rec[4]);
        author.setModified(false);
    case 4: chatname = convert<const std::string&, std::string>(rec[3]);
        chatname.setModified(false);
    case 3: convo_id = convert<const std::string&, int>(rec[2]);
        convo_id.setModified(false);
    case 2: is_permanent = convert<const std::string&, int>(rec[1]);
        is_permanent.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Messages::Messages(const Messages& obj)
     : litesql::Persistent(obj), id(obj.id), is_permanent(obj.is_permanent), convo_id(obj.convo_id), chatname(obj.chatname), author(obj.author), from_dispname(obj.from_dispname), author_was_live(obj.author_was_live), guid(obj.guid), dialog_partner(obj.dialog_partner), timestamp(obj.timestamp), sending_status(obj.sending_status), consumption_status(obj.consumption_status), edited_by(obj.edited_by), edited_timestamp(obj.edited_timestamp), param_key(obj.param_key), param_value(obj.param_value), body_xml(obj.body_xml), identities(obj.identities), reason(obj.reason), leavereason(obj.leavereason), participant_count(obj.participant_count), error_code(obj.error_code), chatmsg_type(obj.chatmsg_type), chatmsg_status(obj.chatmsg_status), body_is_rawxml(obj.body_is_rawxml), oldoptions(obj.oldoptions), newoptions(obj.newoptions), newrole(obj.newrole), pk_id(obj.pk_id), crc(obj.crc), remote_id(obj.remote_id), call_guid(obj.call_guid) {
}
const Messages& Messages::operator=(const Messages& obj) {
    if (this != &obj) {
        id = obj.id;
        is_permanent = obj.is_permanent;
        convo_id = obj.convo_id;
        chatname = obj.chatname;
        author = obj.author;
        from_dispname = obj.from_dispname;
        author_was_live = obj.author_was_live;
        guid = obj.guid;
        dialog_partner = obj.dialog_partner;
        timestamp = obj.timestamp;
        sending_status = obj.sending_status;
        consumption_status = obj.consumption_status;
        edited_by = obj.edited_by;
        edited_timestamp = obj.edited_timestamp;
        param_key = obj.param_key;
        param_value = obj.param_value;
        body_xml = obj.body_xml;
        identities = obj.identities;
        reason = obj.reason;
        leavereason = obj.leavereason;
        participant_count = obj.participant_count;
        error_code = obj.error_code;
        chatmsg_type = obj.chatmsg_type;
        chatmsg_status = obj.chatmsg_status;
        body_is_rawxml = obj.body_is_rawxml;
        oldoptions = obj.oldoptions;
        newoptions = obj.newoptions;
        newrole = obj.newrole;
        pk_id = obj.pk_id;
        crc = obj.crc;
        remote_id = obj.remote_id;
        call_guid = obj.call_guid;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string Messages::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(is_permanent.name());
    values.push_back(is_permanent);
    is_permanent.setModified(false);
    fields.push_back(convo_id.name());
    values.push_back(convo_id);
    convo_id.setModified(false);
    fields.push_back(chatname.name());
    values.push_back(chatname);
    chatname.setModified(false);
    fields.push_back(author.name());
    values.push_back(author);
    author.setModified(false);
    fields.push_back(from_dispname.name());
    values.push_back(from_dispname);
    from_dispname.setModified(false);
    fields.push_back(author_was_live.name());
    values.push_back(author_was_live);
    author_was_live.setModified(false);
    fields.push_back(guid.name());
    values.push_back(guid);
    guid.setModified(false);
    fields.push_back(dialog_partner.name());
    values.push_back(dialog_partner);
    dialog_partner.setModified(false);
    fields.push_back(timestamp.name());
    values.push_back(timestamp);
    timestamp.setModified(false);
    fields.push_back(sending_status.name());
    values.push_back(sending_status);
    sending_status.setModified(false);
    fields.push_back(consumption_status.name());
    values.push_back(consumption_status);
    consumption_status.setModified(false);
    fields.push_back(edited_by.name());
    values.push_back(edited_by);
    edited_by.setModified(false);
    fields.push_back(edited_timestamp.name());
    values.push_back(edited_timestamp);
    edited_timestamp.setModified(false);
    fields.push_back(param_key.name());
    values.push_back(param_key);
    param_key.setModified(false);
    fields.push_back(param_value.name());
    values.push_back(param_value);
    param_value.setModified(false);
    fields.push_back(body_xml.name());
    values.push_back(body_xml);
    body_xml.setModified(false);
    fields.push_back(identities.name());
    values.push_back(identities);
    identities.setModified(false);
    fields.push_back(reason.name());
    values.push_back(reason);
    reason.setModified(false);
    fields.push_back(leavereason.name());
    values.push_back(leavereason);
    leavereason.setModified(false);
    fields.push_back(participant_count.name());
    values.push_back(participant_count);
    participant_count.setModified(false);
    fields.push_back(error_code.name());
    values.push_back(error_code);
    error_code.setModified(false);
    fields.push_back(chatmsg_type.name());
    values.push_back(chatmsg_type);
    chatmsg_type.setModified(false);
    fields.push_back(chatmsg_status.name());
    values.push_back(chatmsg_status);
    chatmsg_status.setModified(false);
    fields.push_back(body_is_rawxml.name());
    values.push_back(body_is_rawxml);
    body_is_rawxml.setModified(false);
    fields.push_back(oldoptions.name());
    values.push_back(oldoptions);
    oldoptions.setModified(false);
    fields.push_back(newoptions.name());
    values.push_back(newoptions);
    newoptions.setModified(false);
    fields.push_back(newrole.name());
    values.push_back(newrole);
    newrole.setModified(false);
    fields.push_back(pk_id.name());
    values.push_back(pk_id);
    pk_id.setModified(false);
    fields.push_back(crc.name());
    values.push_back(crc);
    crc.setModified(false);
    fields.push_back(remote_id.name());
    values.push_back(remote_id);
    remote_id.setModified(false);
    fields.push_back(call_guid.name());
    values.push_back(call_guid);
    call_guid.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Messages::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    //Type processing disabled
    //type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Messages::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, is_permanent);
    updateField(updates, table__, convo_id);
    updateField(updates, table__, chatname);
    updateField(updates, table__, author);
    updateField(updates, table__, from_dispname);
    updateField(updates, table__, author_was_live);
    updateField(updates, table__, guid);
    updateField(updates, table__, dialog_partner);
    updateField(updates, table__, timestamp);
    updateField(updates, table__, sending_status);
    updateField(updates, table__, consumption_status);
    updateField(updates, table__, edited_by);
    updateField(updates, table__, edited_timestamp);
    updateField(updates, table__, param_key);
    updateField(updates, table__, param_value);
    updateField(updates, table__, body_xml);
    updateField(updates, table__, identities);
    updateField(updates, table__, reason);
    updateField(updates, table__, leavereason);
    updateField(updates, table__, participant_count);
    updateField(updates, table__, error_code);
    updateField(updates, table__, chatmsg_type);
    updateField(updates, table__, chatmsg_status);
    updateField(updates, table__, body_is_rawxml);
    updateField(updates, table__, oldoptions);
    updateField(updates, table__, newoptions);
    updateField(updates, table__, newrole);
    updateField(updates, table__, pk_id);
    updateField(updates, table__, crc);
    updateField(updates, table__, remote_id);
    updateField(updates, table__, call_guid);
}
void Messages::addIDUpdates(Updates& updates) {
}
void Messages::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Is_permanent);
    ftypes.push_back(Convo_id);
    ftypes.push_back(Chatname);
    ftypes.push_back(Author);
    ftypes.push_back(From_dispname);
    ftypes.push_back(Author_was_live);
    ftypes.push_back(Guid);
    ftypes.push_back(Dialog_partner);
    ftypes.push_back(Timestamp);
    ftypes.push_back(Sending_status);
    ftypes.push_back(Consumption_status);
    ftypes.push_back(Edited_by);
    ftypes.push_back(Edited_timestamp);
    ftypes.push_back(Param_key);
    ftypes.push_back(Param_value);
    ftypes.push_back(Body_xml);
    ftypes.push_back(Identities);
    ftypes.push_back(Reason);
    ftypes.push_back(Leavereason);
    ftypes.push_back(Participant_count);
    ftypes.push_back(Error_code);
    ftypes.push_back(Chatmsg_type);
    ftypes.push_back(Chatmsg_status);
    ftypes.push_back(Body_is_rawxml);
    ftypes.push_back(Oldoptions);
    ftypes.push_back(Newoptions);
    ftypes.push_back(Newrole);
    ftypes.push_back(Pk_id);
    ftypes.push_back(Crc);
    ftypes.push_back(Remote_id);
    ftypes.push_back(Call_guid);
}
void Messages::delRecord() {
    deleteFromTable(table__, id);
}
void Messages::delRelations() {
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
    return true;
}
std::unique_ptr<Messages> Messages::upcast() const {
    return unique_ptr<Messages>(new Messages(*this));
}
std::unique_ptr<Messages> Messages::upcastCopy() const {
    Messages* np = new Messages(*this);
    np->id = id;
    np->is_permanent = is_permanent;
    np->convo_id = convo_id;
    np->chatname = chatname;
    np->author = author;
    np->from_dispname = from_dispname;
    np->author_was_live = author_was_live;
    np->guid = guid;
    np->dialog_partner = dialog_partner;
    np->timestamp = timestamp;
    np->sending_status = sending_status;
    np->consumption_status = consumption_status;
    np->edited_by = edited_by;
    np->edited_timestamp = edited_timestamp;
    np->param_key = param_key;
    np->param_value = param_value;
    np->body_xml = body_xml;
    np->identities = identities;
    np->reason = reason;
    np->leavereason = leavereason;
    np->participant_count = participant_count;
    np->error_code = error_code;
    np->chatmsg_type = chatmsg_type;
    np->chatmsg_status = chatmsg_status;
    np->body_is_rawxml = body_is_rawxml;
    np->oldoptions = oldoptions;
    np->newoptions = newoptions;
    np->newrole = newrole;
    np->pk_id = pk_id;
    np->crc = crc;
    np->remote_id = remote_id;
    np->call_guid = call_guid;
    np->inDatabase = inDatabase;
    return unique_ptr<Messages>(np);
}
std::ostream & operator<<(std::ostream& os, Messages o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.is_permanent.name() << " = " << o.is_permanent << std::endl;
    os << o.convo_id.name() << " = " << o.convo_id << std::endl;
    os << o.chatname.name() << " = " << o.chatname << std::endl;
    os << o.author.name() << " = " << o.author << std::endl;
    os << o.from_dispname.name() << " = " << o.from_dispname << std::endl;
    os << o.author_was_live.name() << " = " << o.author_was_live << std::endl;
    os << o.guid.name() << " = " << o.guid << std::endl;
    os << o.dialog_partner.name() << " = " << o.dialog_partner << std::endl;
    os << o.timestamp.name() << " = " << o.timestamp << std::endl;
    os << o.sending_status.name() << " = " << o.sending_status << std::endl;
    os << o.consumption_status.name() << " = " << o.consumption_status << std::endl;
    os << o.edited_by.name() << " = " << o.edited_by << std::endl;
    os << o.edited_timestamp.name() << " = " << o.edited_timestamp << std::endl;
    os << o.param_key.name() << " = " << o.param_key << std::endl;
    os << o.param_value.name() << " = " << o.param_value << std::endl;
    os << o.body_xml.name() << " = " << o.body_xml << std::endl;
    os << o.identities.name() << " = " << o.identities << std::endl;
    os << o.reason.name() << " = " << o.reason << std::endl;
    os << o.leavereason.name() << " = " << o.leavereason << std::endl;
    os << o.participant_count.name() << " = " << o.participant_count << std::endl;
    os << o.error_code.name() << " = " << o.error_code << std::endl;
    os << o.chatmsg_type.name() << " = " << o.chatmsg_type << std::endl;
    os << o.chatmsg_status.name() << " = " << o.chatmsg_status << std::endl;
    os << o.body_is_rawxml.name() << " = " << o.body_is_rawxml << std::endl;
    os << o.oldoptions.name() << " = " << o.oldoptions << std::endl;
    os << o.newoptions.name() << " = " << o.newoptions << std::endl;
    os << o.newrole.name() << " = " << o.newrole << std::endl;
    os << o.pk_id.name() << " = " << o.pk_id << std::endl;
    os << o.crc.name() << " = " << o.crc << std::endl;
    os << o.remote_id.name() << " = " << o.remote_id << std::endl;
    os << o.call_guid.name() << " = " << o.call_guid << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Chats::Own::Id("id",A_field_type_integer,"Chats");
const std::string Chats::type__("Chats");
const std::string Chats::table__("Chats");
const std::string Chats::sequence__("Chats_seq");
const litesql::FieldType Chats::Id("id",A_field_type_integer,table__);
const litesql::FieldType Chats::Is_permanent("is_permanent",A_field_type_integer,table__);
const litesql::FieldType Chats::Name("name",A_field_type_string,table__);
const litesql::FieldType Chats::Options("options",A_field_type_integer,table__);
const litesql::FieldType Chats::Friendlyname("friendlyname",A_field_type_string,table__);
const litesql::FieldType Chats::Description("description",A_field_type_string,table__);
const litesql::FieldType Chats::Timestamp("timestamp",A_field_type_integer,table__);
const litesql::FieldType Chats::Activity_timestamp("activity_timestamp",A_field_type_integer,table__);
const litesql::FieldType Chats::Dialog_partner("dialog_partner",A_field_type_string,table__);
const litesql::FieldType Chats::Adder("adder",A_field_type_string,table__);
const litesql::FieldType Chats::Mystatus("mystatus",A_field_type_integer,table__);
const litesql::FieldType Chats::Myrole("myrole",A_field_type_integer,table__);
const litesql::FieldType Chats::Posters("posters",A_field_type_string,table__);
const litesql::FieldType Chats::Participants("participants",A_field_type_string,table__);
const litesql::FieldType Chats::Applicants("applicants",A_field_type_string,table__);
const litesql::FieldType Chats::Banned_users("banned_users",A_field_type_string,table__);
const litesql::FieldType Chats::Name_text("name_text",A_field_type_string,table__);
const litesql::FieldType Chats::Topic("topic",A_field_type_string,table__);
const litesql::FieldType Chats::Topic_xml("topic_xml",A_field_type_string,table__);
const litesql::FieldType Chats::Guidelines("guidelines",A_field_type_string,table__);
const litesql::FieldType Chats::Picture("picture",A_field_type_blob,table__);
const litesql::FieldType Chats::Alertstring("alertstring",A_field_type_string,table__);
const litesql::FieldType Chats::Is_bookmarked("is_bookmarked",A_field_type_integer,table__);
const litesql::FieldType Chats::Passwordhint("passwordhint",A_field_type_string,table__);
const litesql::FieldType Chats::Unconsumed_suppressed_msg("unconsumed_suppressed_msg",A_field_type_integer,table__);
const litesql::FieldType Chats::Unconsumed_normal_msg("unconsumed_normal_msg",A_field_type_integer,table__);
const litesql::FieldType Chats::Unconsumed_elevated_msg("unconsumed_elevated_msg",A_field_type_integer,table__);
const litesql::FieldType Chats::Unconsumed_msg_voice("unconsumed_msg_voice",A_field_type_integer,table__);
const litesql::FieldType Chats::Activemembers("activemembers",A_field_type_string,table__);
const litesql::FieldType Chats::State_data("state_data",A_field_type_blob,table__);
const litesql::FieldType Chats::Lifesigns("lifesigns",A_field_type_integer,table__);
const litesql::FieldType Chats::Last_change("last_change",A_field_type_integer,table__);
const litesql::FieldType Chats::First_unread_message("first_unread_message",A_field_type_integer,table__);
const litesql::FieldType Chats::Pk_type("pk_type",A_field_type_integer,table__);
const litesql::FieldType Chats::Dbpath("dbpath",A_field_type_string,table__);
const litesql::FieldType Chats::Split_friendlyname("split_friendlyname",A_field_type_string,table__);
const litesql::FieldType Chats::Conv_dbid("conv_dbid",A_field_type_integer,table__);
void Chats::initValues() {
}
void Chats::defaults() {
    id = 0;
    is_permanent = 0;
    options = 0;
    timestamp = 0;
    activity_timestamp = 0;
    mystatus = 0;
    myrole = 0;
    picture = Blob();
    is_bookmarked = 0;
    unconsumed_suppressed_msg = 0;
    unconsumed_normal_msg = 0;
    unconsumed_elevated_msg = 0;
    unconsumed_msg_voice = 0;
    state_data = Blob();
    lifesigns = 0;
    last_change = 0;
    first_unread_message = 0;
    pk_type = 0;
    conv_dbid = 0;
}
Chats::Chats(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), is_permanent(Is_permanent), name(Name), options(Options), friendlyname(Friendlyname), description(Description), timestamp(Timestamp), activity_timestamp(Activity_timestamp), dialog_partner(Dialog_partner), adder(Adder), mystatus(Mystatus), myrole(Myrole), posters(Posters), participants(Participants), applicants(Applicants), banned_users(Banned_users), name_text(Name_text), topic(Topic), topic_xml(Topic_xml), guidelines(Guidelines), picture(Picture), alertstring(Alertstring), is_bookmarked(Is_bookmarked), passwordhint(Passwordhint), unconsumed_suppressed_msg(Unconsumed_suppressed_msg), unconsumed_normal_msg(Unconsumed_normal_msg), unconsumed_elevated_msg(Unconsumed_elevated_msg), unconsumed_msg_voice(Unconsumed_msg_voice), activemembers(Activemembers), state_data(State_data), lifesigns(Lifesigns), last_change(Last_change), first_unread_message(First_unread_message), pk_type(Pk_type), dbpath(Dbpath), split_friendlyname(Split_friendlyname), conv_dbid(Conv_dbid) {
    defaults();
}
Chats::Chats(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), is_permanent(Is_permanent), name(Name), options(Options), friendlyname(Friendlyname), description(Description), timestamp(Timestamp), activity_timestamp(Activity_timestamp), dialog_partner(Dialog_partner), adder(Adder), mystatus(Mystatus), myrole(Myrole), posters(Posters), participants(Participants), applicants(Applicants), banned_users(Banned_users), name_text(Name_text), topic(Topic), topic_xml(Topic_xml), guidelines(Guidelines), picture(Picture), alertstring(Alertstring), is_bookmarked(Is_bookmarked), passwordhint(Passwordhint), unconsumed_suppressed_msg(Unconsumed_suppressed_msg), unconsumed_normal_msg(Unconsumed_normal_msg), unconsumed_elevated_msg(Unconsumed_elevated_msg), unconsumed_msg_voice(Unconsumed_msg_voice), activemembers(Activemembers), state_data(State_data), lifesigns(Lifesigns), last_change(Last_change), first_unread_message(First_unread_message), pk_type(Pk_type), dbpath(Dbpath), split_friendlyname(Split_friendlyname), conv_dbid(Conv_dbid) {
    defaults();
    size_t size = (rec.size() > 37) ? 37 : rec.size();
    switch(size) {
    case 37: conv_dbid = convert<const std::string&, int>(rec[36]);
        conv_dbid.setModified(false);
    case 36: split_friendlyname = convert<const std::string&, std::string>(rec[35]);
        split_friendlyname.setModified(false);
    case 35: dbpath = convert<const std::string&, std::string>(rec[34]);
        dbpath.setModified(false);
    case 34: pk_type = convert<const std::string&, int>(rec[33]);
        pk_type.setModified(false);
    case 33: first_unread_message = convert<const std::string&, int>(rec[32]);
        first_unread_message.setModified(false);
    case 32: last_change = convert<const std::string&, int>(rec[31]);
        last_change.setModified(false);
    case 31: lifesigns = convert<const std::string&, int>(rec[30]);
        lifesigns.setModified(false);
    case 30: state_data = convert<const std::string&, litesql::Blob>(rec[29]);
        state_data.setModified(false);
    case 29: activemembers = convert<const std::string&, std::string>(rec[28]);
        activemembers.setModified(false);
    case 28: unconsumed_msg_voice = convert<const std::string&, int>(rec[27]);
        unconsumed_msg_voice.setModified(false);
    case 27: unconsumed_elevated_msg = convert<const std::string&, int>(rec[26]);
        unconsumed_elevated_msg.setModified(false);
    case 26: unconsumed_normal_msg = convert<const std::string&, int>(rec[25]);
        unconsumed_normal_msg.setModified(false);
    case 25: unconsumed_suppressed_msg = convert<const std::string&, int>(rec[24]);
        unconsumed_suppressed_msg.setModified(false);
    case 24: passwordhint = convert<const std::string&, std::string>(rec[23]);
        passwordhint.setModified(false);
    case 23: is_bookmarked = convert<const std::string&, int>(rec[22]);
        is_bookmarked.setModified(false);
    case 22: alertstring = convert<const std::string&, std::string>(rec[21]);
        alertstring.setModified(false);
    case 21: picture = convert<const std::string&, litesql::Blob>(rec[20]);
        picture.setModified(false);
    case 20: guidelines = convert<const std::string&, std::string>(rec[19]);
        guidelines.setModified(false);
    case 19: topic_xml = convert<const std::string&, std::string>(rec[18]);
        topic_xml.setModified(false);
    case 18: topic = convert<const std::string&, std::string>(rec[17]);
        topic.setModified(false);
    case 17: name_text = convert<const std::string&, std::string>(rec[16]);
        name_text.setModified(false);
    case 16: banned_users = convert<const std::string&, std::string>(rec[15]);
        banned_users.setModified(false);
    case 15: applicants = convert<const std::string&, std::string>(rec[14]);
        applicants.setModified(false);
    case 14: participants = convert<const std::string&, std::string>(rec[13]);
        participants.setModified(false);
    case 13: posters = convert<const std::string&, std::string>(rec[12]);
        posters.setModified(false);
    case 12: myrole = convert<const std::string&, int>(rec[11]);
        myrole.setModified(false);
    case 11: mystatus = convert<const std::string&, int>(rec[10]);
        mystatus.setModified(false);
    case 10: adder = convert<const std::string&, std::string>(rec[9]);
        adder.setModified(false);
    case 9: dialog_partner = convert<const std::string&, std::string>(rec[8]);
        dialog_partner.setModified(false);
    case 8: activity_timestamp = convert<const std::string&, int>(rec[7]);
        activity_timestamp.setModified(false);
    case 7: timestamp = convert<const std::string&, int>(rec[6]);
        timestamp.setModified(false);
    case 6: description = convert<const std::string&, std::string>(rec[5]);
        description.setModified(false);
    case 5: friendlyname = convert<const std::string&, std::string>(rec[4]);
        friendlyname.setModified(false);
    case 4: options = convert<const std::string&, int>(rec[3]);
        options.setModified(false);
    case 3: name = convert<const std::string&, std::string>(rec[2]);
        name.setModified(false);
    case 2: is_permanent = convert<const std::string&, int>(rec[1]);
        is_permanent.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Chats::Chats(const Chats& obj)
     : litesql::Persistent(obj), id(obj.id), is_permanent(obj.is_permanent), name(obj.name), options(obj.options), friendlyname(obj.friendlyname), description(obj.description), timestamp(obj.timestamp), activity_timestamp(obj.activity_timestamp), dialog_partner(obj.dialog_partner), adder(obj.adder), mystatus(obj.mystatus), myrole(obj.myrole), posters(obj.posters), participants(obj.participants), applicants(obj.applicants), banned_users(obj.banned_users), name_text(obj.name_text), topic(obj.topic), topic_xml(obj.topic_xml), guidelines(obj.guidelines), picture(obj.picture), alertstring(obj.alertstring), is_bookmarked(obj.is_bookmarked), passwordhint(obj.passwordhint), unconsumed_suppressed_msg(obj.unconsumed_suppressed_msg), unconsumed_normal_msg(obj.unconsumed_normal_msg), unconsumed_elevated_msg(obj.unconsumed_elevated_msg), unconsumed_msg_voice(obj.unconsumed_msg_voice), activemembers(obj.activemembers), state_data(obj.state_data), lifesigns(obj.lifesigns), last_change(obj.last_change), first_unread_message(obj.first_unread_message), pk_type(obj.pk_type), dbpath(obj.dbpath), split_friendlyname(obj.split_friendlyname), conv_dbid(obj.conv_dbid) {
}
const Chats& Chats::operator=(const Chats& obj) {
    if (this != &obj) {
        id = obj.id;
        is_permanent = obj.is_permanent;
        name = obj.name;
        options = obj.options;
        friendlyname = obj.friendlyname;
        description = obj.description;
        timestamp = obj.timestamp;
        activity_timestamp = obj.activity_timestamp;
        dialog_partner = obj.dialog_partner;
        adder = obj.adder;
        mystatus = obj.mystatus;
        myrole = obj.myrole;
        posters = obj.posters;
        participants = obj.participants;
        applicants = obj.applicants;
        banned_users = obj.banned_users;
        name_text = obj.name_text;
        topic = obj.topic;
        topic_xml = obj.topic_xml;
        guidelines = obj.guidelines;
        picture = obj.picture;
        alertstring = obj.alertstring;
        is_bookmarked = obj.is_bookmarked;
        passwordhint = obj.passwordhint;
        unconsumed_suppressed_msg = obj.unconsumed_suppressed_msg;
        unconsumed_normal_msg = obj.unconsumed_normal_msg;
        unconsumed_elevated_msg = obj.unconsumed_elevated_msg;
        unconsumed_msg_voice = obj.unconsumed_msg_voice;
        activemembers = obj.activemembers;
        state_data = obj.state_data;
        lifesigns = obj.lifesigns;
        last_change = obj.last_change;
        first_unread_message = obj.first_unread_message;
        pk_type = obj.pk_type;
        dbpath = obj.dbpath;
        split_friendlyname = obj.split_friendlyname;
        conv_dbid = obj.conv_dbid;
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
    fields.push_back(is_permanent.name());
    values.push_back(is_permanent);
    is_permanent.setModified(false);
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fields.push_back(options.name());
    values.push_back(options);
    options.setModified(false);
    fields.push_back(friendlyname.name());
    values.push_back(friendlyname);
    friendlyname.setModified(false);
    fields.push_back(description.name());
    values.push_back(description);
    description.setModified(false);
    fields.push_back(timestamp.name());
    values.push_back(timestamp);
    timestamp.setModified(false);
    fields.push_back(activity_timestamp.name());
    values.push_back(activity_timestamp);
    activity_timestamp.setModified(false);
    fields.push_back(dialog_partner.name());
    values.push_back(dialog_partner);
    dialog_partner.setModified(false);
    fields.push_back(adder.name());
    values.push_back(adder);
    adder.setModified(false);
    fields.push_back(mystatus.name());
    values.push_back(mystatus);
    mystatus.setModified(false);
    fields.push_back(myrole.name());
    values.push_back(myrole);
    myrole.setModified(false);
    fields.push_back(posters.name());
    values.push_back(posters);
    posters.setModified(false);
    fields.push_back(participants.name());
    values.push_back(participants);
    participants.setModified(false);
    fields.push_back(applicants.name());
    values.push_back(applicants);
    applicants.setModified(false);
    fields.push_back(banned_users.name());
    values.push_back(banned_users);
    banned_users.setModified(false);
    fields.push_back(name_text.name());
    values.push_back(name_text);
    name_text.setModified(false);
    fields.push_back(topic.name());
    values.push_back(topic);
    topic.setModified(false);
    fields.push_back(topic_xml.name());
    values.push_back(topic_xml);
    topic_xml.setModified(false);
    fields.push_back(guidelines.name());
    values.push_back(guidelines);
    guidelines.setModified(false);
    fields.push_back(picture.name());
    values.push_back(picture);
    picture.setModified(false);
    fields.push_back(alertstring.name());
    values.push_back(alertstring);
    alertstring.setModified(false);
    fields.push_back(is_bookmarked.name());
    values.push_back(is_bookmarked);
    is_bookmarked.setModified(false);
    fields.push_back(passwordhint.name());
    values.push_back(passwordhint);
    passwordhint.setModified(false);
    fields.push_back(unconsumed_suppressed_msg.name());
    values.push_back(unconsumed_suppressed_msg);
    unconsumed_suppressed_msg.setModified(false);
    fields.push_back(unconsumed_normal_msg.name());
    values.push_back(unconsumed_normal_msg);
    unconsumed_normal_msg.setModified(false);
    fields.push_back(unconsumed_elevated_msg.name());
    values.push_back(unconsumed_elevated_msg);
    unconsumed_elevated_msg.setModified(false);
    fields.push_back(unconsumed_msg_voice.name());
    values.push_back(unconsumed_msg_voice);
    unconsumed_msg_voice.setModified(false);
    fields.push_back(activemembers.name());
    values.push_back(activemembers);
    activemembers.setModified(false);
    fields.push_back(state_data.name());
    values.push_back(state_data);
    state_data.setModified(false);
    fields.push_back(lifesigns.name());
    values.push_back(lifesigns);
    lifesigns.setModified(false);
    fields.push_back(last_change.name());
    values.push_back(last_change);
    last_change.setModified(false);
    fields.push_back(first_unread_message.name());
    values.push_back(first_unread_message);
    first_unread_message.setModified(false);
    fields.push_back(pk_type.name());
    values.push_back(pk_type);
    pk_type.setModified(false);
    fields.push_back(dbpath.name());
    values.push_back(dbpath);
    dbpath.setModified(false);
    fields.push_back(split_friendlyname.name());
    values.push_back(split_friendlyname);
    split_friendlyname.setModified(false);
    fields.push_back(conv_dbid.name());
    values.push_back(conv_dbid);
    conv_dbid.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Chats::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    //Type processing disabled
    //type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Chats::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, is_permanent);
    updateField(updates, table__, name);
    updateField(updates, table__, options);
    updateField(updates, table__, friendlyname);
    updateField(updates, table__, description);
    updateField(updates, table__, timestamp);
    updateField(updates, table__, activity_timestamp);
    updateField(updates, table__, dialog_partner);
    updateField(updates, table__, adder);
    updateField(updates, table__, mystatus);
    updateField(updates, table__, myrole);
    updateField(updates, table__, posters);
    updateField(updates, table__, participants);
    updateField(updates, table__, applicants);
    updateField(updates, table__, banned_users);
    updateField(updates, table__, name_text);
    updateField(updates, table__, topic);
    updateField(updates, table__, topic_xml);
    updateField(updates, table__, guidelines);
    updateField(updates, table__, picture);
    updateField(updates, table__, alertstring);
    updateField(updates, table__, is_bookmarked);
    updateField(updates, table__, passwordhint);
    updateField(updates, table__, unconsumed_suppressed_msg);
    updateField(updates, table__, unconsumed_normal_msg);
    updateField(updates, table__, unconsumed_elevated_msg);
    updateField(updates, table__, unconsumed_msg_voice);
    updateField(updates, table__, activemembers);
    updateField(updates, table__, state_data);
    updateField(updates, table__, lifesigns);
    updateField(updates, table__, last_change);
    updateField(updates, table__, first_unread_message);
    updateField(updates, table__, pk_type);
    updateField(updates, table__, dbpath);
    updateField(updates, table__, split_friendlyname);
    updateField(updates, table__, conv_dbid);
}
void Chats::addIDUpdates(Updates& updates) {
}
void Chats::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Is_permanent);
    ftypes.push_back(Name);
    ftypes.push_back(Options);
    ftypes.push_back(Friendlyname);
    ftypes.push_back(Description);
    ftypes.push_back(Timestamp);
    ftypes.push_back(Activity_timestamp);
    ftypes.push_back(Dialog_partner);
    ftypes.push_back(Adder);
    ftypes.push_back(Mystatus);
    ftypes.push_back(Myrole);
    ftypes.push_back(Posters);
    ftypes.push_back(Participants);
    ftypes.push_back(Applicants);
    ftypes.push_back(Banned_users);
    ftypes.push_back(Name_text);
    ftypes.push_back(Topic);
    ftypes.push_back(Topic_xml);
    ftypes.push_back(Guidelines);
    ftypes.push_back(Picture);
    ftypes.push_back(Alertstring);
    ftypes.push_back(Is_bookmarked);
    ftypes.push_back(Passwordhint);
    ftypes.push_back(Unconsumed_suppressed_msg);
    ftypes.push_back(Unconsumed_normal_msg);
    ftypes.push_back(Unconsumed_elevated_msg);
    ftypes.push_back(Unconsumed_msg_voice);
    ftypes.push_back(Activemembers);
    ftypes.push_back(State_data);
    ftypes.push_back(Lifesigns);
    ftypes.push_back(Last_change);
    ftypes.push_back(First_unread_message);
    ftypes.push_back(Pk_type);
    ftypes.push_back(Dbpath);
    ftypes.push_back(Split_friendlyname);
    ftypes.push_back(Conv_dbid);
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
    return true;
}
std::unique_ptr<Chats> Chats::upcast() const {
    return unique_ptr<Chats>(new Chats(*this));
}
std::unique_ptr<Chats> Chats::upcastCopy() const {
    Chats* np = new Chats(*this);
    np->id = id;
    np->is_permanent = is_permanent;
    np->name = name;
    np->options = options;
    np->friendlyname = friendlyname;
    np->description = description;
    np->timestamp = timestamp;
    np->activity_timestamp = activity_timestamp;
    np->dialog_partner = dialog_partner;
    np->adder = adder;
    np->mystatus = mystatus;
    np->myrole = myrole;
    np->posters = posters;
    np->participants = participants;
    np->applicants = applicants;
    np->banned_users = banned_users;
    np->name_text = name_text;
    np->topic = topic;
    np->topic_xml = topic_xml;
    np->guidelines = guidelines;
    np->picture = picture;
    np->alertstring = alertstring;
    np->is_bookmarked = is_bookmarked;
    np->passwordhint = passwordhint;
    np->unconsumed_suppressed_msg = unconsumed_suppressed_msg;
    np->unconsumed_normal_msg = unconsumed_normal_msg;
    np->unconsumed_elevated_msg = unconsumed_elevated_msg;
    np->unconsumed_msg_voice = unconsumed_msg_voice;
    np->activemembers = activemembers;
    np->state_data = state_data;
    np->lifesigns = lifesigns;
    np->last_change = last_change;
    np->first_unread_message = first_unread_message;
    np->pk_type = pk_type;
    np->dbpath = dbpath;
    np->split_friendlyname = split_friendlyname;
    np->conv_dbid = conv_dbid;
    np->inDatabase = inDatabase;
    return unique_ptr<Chats>(np);
}
std::ostream & operator<<(std::ostream& os, Chats o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.is_permanent.name() << " = " << o.is_permanent << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << o.options.name() << " = " << o.options << std::endl;
    os << o.friendlyname.name() << " = " << o.friendlyname << std::endl;
    os << o.description.name() << " = " << o.description << std::endl;
    os << o.timestamp.name() << " = " << o.timestamp << std::endl;
    os << o.activity_timestamp.name() << " = " << o.activity_timestamp << std::endl;
    os << o.dialog_partner.name() << " = " << o.dialog_partner << std::endl;
    os << o.adder.name() << " = " << o.adder << std::endl;
    os << o.mystatus.name() << " = " << o.mystatus << std::endl;
    os << o.myrole.name() << " = " << o.myrole << std::endl;
    os << o.posters.name() << " = " << o.posters << std::endl;
    os << o.participants.name() << " = " << o.participants << std::endl;
    os << o.applicants.name() << " = " << o.applicants << std::endl;
    os << o.banned_users.name() << " = " << o.banned_users << std::endl;
    os << o.name_text.name() << " = " << o.name_text << std::endl;
    os << o.topic.name() << " = " << o.topic << std::endl;
    os << o.topic_xml.name() << " = " << o.topic_xml << std::endl;
    os << o.guidelines.name() << " = " << o.guidelines << std::endl;
    os << o.picture.name() << " = " << o.picture << std::endl;
    os << o.alertstring.name() << " = " << o.alertstring << std::endl;
    os << o.is_bookmarked.name() << " = " << o.is_bookmarked << std::endl;
    os << o.passwordhint.name() << " = " << o.passwordhint << std::endl;
    os << o.unconsumed_suppressed_msg.name() << " = " << o.unconsumed_suppressed_msg << std::endl;
    os << o.unconsumed_normal_msg.name() << " = " << o.unconsumed_normal_msg << std::endl;
    os << o.unconsumed_elevated_msg.name() << " = " << o.unconsumed_elevated_msg << std::endl;
    os << o.unconsumed_msg_voice.name() << " = " << o.unconsumed_msg_voice << std::endl;
    os << o.activemembers.name() << " = " << o.activemembers << std::endl;
    os << o.state_data.name() << " = " << o.state_data << std::endl;
    os << o.lifesigns.name() << " = " << o.lifesigns << std::endl;
    os << o.last_change.name() << " = " << o.last_change << std::endl;
    os << o.first_unread_message.name() << " = " << o.first_unread_message << std::endl;
    os << o.pk_type.name() << " = " << o.pk_type << std::endl;
    os << o.dbpath.name() << " = " << o.dbpath << std::endl;
    os << o.split_friendlyname.name() << " = " << o.split_friendlyname << std::endl;
    os << o.conv_dbid.name() << " = " << o.conv_dbid << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Contacts::Own::Id("id",A_field_type_integer,"Contacts");
const std::string Contacts::type__("Contacts");
const std::string Contacts::table__("Contacts");
const std::string Contacts::sequence__("Contacts_seq");
const litesql::FieldType Contacts::Id("id",A_field_type_integer,table__);
const litesql::FieldType Contacts::Is_permanent("is_permanent",A_field_type_integer,table__);
const litesql::FieldType Contacts::Skypename("skypename",A_field_type_string,table__);
const litesql::FieldType Contacts::Pstnnumber("pstnnumber",A_field_type_string,table__);
const litesql::FieldType Contacts::Aliases("aliases",A_field_type_string,table__);
const litesql::FieldType Contacts::Fullname("fullname",A_field_type_string,table__);
const litesql::FieldType Contacts::Birthday("birthday",A_field_type_integer,table__);
const litesql::FieldType Contacts::Gender("gender",A_field_type_integer,table__);
const litesql::FieldType Contacts::Languages("languages",A_field_type_string,table__);
const litesql::FieldType Contacts::Country("country",A_field_type_string,table__);
const litesql::FieldType Contacts::Province("province",A_field_type_string,table__);
const litesql::FieldType Contacts::City("city",A_field_type_string,table__);
const litesql::FieldType Contacts::Phone_home("phone_home",A_field_type_string,table__);
const litesql::FieldType Contacts::Phone_office("phone_office",A_field_type_string,table__);
const litesql::FieldType Contacts::Phone_mobile("phone_mobile",A_field_type_string,table__);
const litesql::FieldType Contacts::Emails("emails",A_field_type_string,table__);
const litesql::FieldType Contacts::Homepage("homepage",A_field_type_string,table__);
const litesql::FieldType Contacts::About("about",A_field_type_string,table__);
const litesql::FieldType Contacts::Mood_text("mood_text",A_field_type_string,table__);
const litesql::FieldType Contacts::Rich_mood_text("rich_mood_text",A_field_type_string,table__);
const litesql::FieldType Contacts::Timezone("timezone",A_field_type_integer,table__);
const litesql::FieldType Contacts::Profile_timestamp("profile_timestamp",A_field_type_integer,table__);
const litesql::FieldType Contacts::Nrof_authed_buddies("nrof_authed_buddies",A_field_type_integer,table__);
const litesql::FieldType Contacts::Ipcountry("ipcountry",A_field_type_string,table__);
const litesql::FieldType Contacts::Avatar_timestamp("avatar_timestamp",A_field_type_integer,table__);
const litesql::FieldType Contacts::Mood_timestamp("mood_timestamp",A_field_type_integer,table__);
const litesql::FieldType Contacts::Received_authrequest("received_authrequest",A_field_type_string,table__);
const litesql::FieldType Contacts::Authreq_timestamp("authreq_timestamp",A_field_type_integer,table__);
const litesql::FieldType Contacts::Lastonline_timestamp("lastonline_timestamp",A_field_type_integer,table__);
const litesql::FieldType Contacts::Availability("availability",A_field_type_integer,table__);
const litesql::FieldType Contacts::Displayname("displayname",A_field_type_string,table__);
const litesql::FieldType Contacts::Refreshing("refreshing",A_field_type_integer,table__);
const litesql::FieldType Contacts::Given_authlevel("given_authlevel",A_field_type_integer,table__);
const litesql::FieldType Contacts::Given_displayname("given_displayname",A_field_type_string,table__);
const litesql::FieldType Contacts::Assigned_speeddial("assigned_speeddial",A_field_type_string,table__);
const litesql::FieldType Contacts::Assigned_comment("assigned_comment",A_field_type_string,table__);
const litesql::FieldType Contacts::Alertstring("alertstring",A_field_type_string,table__);
const litesql::FieldType Contacts::Lastused_timestamp("lastused_timestamp",A_field_type_integer,table__);
const litesql::FieldType Contacts::Authrequest_count("authrequest_count",A_field_type_integer,table__);
const litesql::FieldType Contacts::Assigned_phone1("assigned_phone1",A_field_type_string,table__);
const litesql::FieldType Contacts::Assigned_phone1_label("assigned_phone1_label",A_field_type_string,table__);
const litesql::FieldType Contacts::Assigned_phone2("assigned_phone2",A_field_type_string,table__);
const litesql::FieldType Contacts::Assigned_phone2_label("assigned_phone2_label",A_field_type_string,table__);
const litesql::FieldType Contacts::Assigned_phone3("assigned_phone3",A_field_type_string,table__);
const litesql::FieldType Contacts::Assigned_phone3_label("assigned_phone3_label",A_field_type_string,table__);
const litesql::FieldType Contacts::Buddystatus("buddystatus",A_field_type_integer,table__);
const litesql::FieldType Contacts::Isauthorized("isauthorized",A_field_type_integer,table__);
const litesql::FieldType Contacts::Popularity_ord("popularity_ord",A_field_type_integer,table__);
const litesql::FieldType Contacts::Isblocked("isblocked",A_field_type_integer,table__);
const litesql::FieldType Contacts::Certificate_send_count("certificate_send_count",A_field_type_integer,table__);
const litesql::FieldType Contacts::Account_modification_serial_nr("account_modification_serial_nr",A_field_type_integer,table__);
const litesql::FieldType Contacts::Nr_of_buddies("nr_of_buddies",A_field_type_integer,table__);
const litesql::FieldType Contacts::Server_synced("server_synced",A_field_type_integer,table__);
const litesql::FieldType Contacts::Contactlist_track("contactlist_track",A_field_type_integer,table__);
const litesql::FieldType Contacts::Last_used_networktime("last_used_networktime",A_field_type_integer,table__);
const litesql::FieldType Contacts::Authorized_time("authorized_time",A_field_type_integer,table__);
const litesql::FieldType Contacts::Sent_authrequest("sent_authrequest",A_field_type_string,table__);
const litesql::FieldType Contacts::Sent_authrequest_time("sent_authrequest_time",A_field_type_integer,table__);
const litesql::FieldType Contacts::Sent_authrequest_serial("sent_authrequest_serial",A_field_type_integer,table__);
const litesql::FieldType Contacts::Node_capabilities("node_capabilities",A_field_type_integer,table__);
const litesql::FieldType Contacts::Revoked_auth("revoked_auth",A_field_type_integer,table__);
const litesql::FieldType Contacts::Added_in_shared_group("added_in_shared_group",A_field_type_integer,table__);
const litesql::FieldType Contacts::In_shared_group("in_shared_group",A_field_type_integer,table__);
const litesql::FieldType Contacts::Stack_version("stack_version",A_field_type_integer,table__);
const litesql::FieldType Contacts::Offline_authreq_id("offline_authreq_id",A_field_type_integer,table__);
const litesql::FieldType Contacts::Node_capabilities_and("node_capabilities_and",A_field_type_integer,table__);
const litesql::FieldType Contacts::Authreq_crc("authreq_crc",A_field_type_integer,table__);
const litesql::FieldType Contacts::Authreq_src("authreq_src",A_field_type_integer,table__);
const litesql::FieldType Contacts::Pop_score("pop_score",A_field_type_integer,table__);
const litesql::FieldType Contacts::Main_phone("main_phone",A_field_type_string,table__);
const litesql::FieldType Contacts::Unified_servants("unified_servants",A_field_type_string,table__);
const litesql::FieldType Contacts::Phone_home_normalized("phone_home_normalized",A_field_type_string,table__);
const litesql::FieldType Contacts::Phone_office_normalized("phone_office_normalized",A_field_type_string,table__);
const litesql::FieldType Contacts::Phone_mobile_normalized("phone_mobile_normalized",A_field_type_string,table__);
const litesql::FieldType Contacts::Sent_authrequest_initmethod("sent_authrequest_initmethod",A_field_type_integer,table__);
const litesql::FieldType Contacts::Authreq_initmethod("authreq_initmethod",A_field_type_integer,table__);
const litesql::FieldType Contacts::Sent_authrequest_extrasbitmask("sent_authrequest_extrasbitmask",A_field_type_integer,table__);
void Contacts::initValues() {
}
void Contacts::defaults() {
    id = 0;
    is_permanent = 0;
    birthday = 0;
    gender = 0;
    timezone = 0;
    profile_timestamp = 0;
    nrof_authed_buddies = 0;
    avatar_timestamp = 0;
    mood_timestamp = 0;
    authreq_timestamp = 0;
    lastonline_timestamp = 0;
    availability = 0;
    refreshing = 0;
    given_authlevel = 0;
    lastused_timestamp = 0;
    authrequest_count = 0;
    buddystatus = 0;
    isauthorized = 0;
    popularity_ord = 0;
    isblocked = 0;
    certificate_send_count = 0;
    account_modification_serial_nr = 0;
    nr_of_buddies = 0;
    server_synced = 0;
    contactlist_track = 0;
    last_used_networktime = 0;
    authorized_time = 0;
    sent_authrequest_time = 0;
    sent_authrequest_serial = 0;
    node_capabilities = 0;
    revoked_auth = 0;
    added_in_shared_group = 0;
    in_shared_group = 0;
    stack_version = 0;
    offline_authreq_id = 0;
    node_capabilities_and = 0;
    authreq_crc = 0;
    authreq_src = 0;
    pop_score = 0;
    sent_authrequest_initmethod = 0;
    authreq_initmethod = 0;
    sent_authrequest_extrasbitmask = 0;
}
Contacts::Contacts(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), is_permanent(Is_permanent), skypename(Skypename), pstnnumber(Pstnnumber), aliases(Aliases), fullname(Fullname), birthday(Birthday), gender(Gender), languages(Languages), country(Country), province(Province), city(City), phone_home(Phone_home), phone_office(Phone_office), phone_mobile(Phone_mobile), emails(Emails), homepage(Homepage), about(About), mood_text(Mood_text), rich_mood_text(Rich_mood_text), timezone(Timezone), profile_timestamp(Profile_timestamp), nrof_authed_buddies(Nrof_authed_buddies), ipcountry(Ipcountry), avatar_timestamp(Avatar_timestamp), mood_timestamp(Mood_timestamp), received_authrequest(Received_authrequest), authreq_timestamp(Authreq_timestamp), lastonline_timestamp(Lastonline_timestamp), availability(Availability), displayname(Displayname), refreshing(Refreshing), given_authlevel(Given_authlevel), given_displayname(Given_displayname), assigned_speeddial(Assigned_speeddial), assigned_comment(Assigned_comment), alertstring(Alertstring), lastused_timestamp(Lastused_timestamp), authrequest_count(Authrequest_count), assigned_phone1(Assigned_phone1), assigned_phone1_label(Assigned_phone1_label), assigned_phone2(Assigned_phone2), assigned_phone2_label(Assigned_phone2_label), assigned_phone3(Assigned_phone3), assigned_phone3_label(Assigned_phone3_label), buddystatus(Buddystatus), isauthorized(Isauthorized), popularity_ord(Popularity_ord), isblocked(Isblocked), certificate_send_count(Certificate_send_count), account_modification_serial_nr(Account_modification_serial_nr), nr_of_buddies(Nr_of_buddies), server_synced(Server_synced), contactlist_track(Contactlist_track), last_used_networktime(Last_used_networktime), authorized_time(Authorized_time), sent_authrequest(Sent_authrequest), sent_authrequest_time(Sent_authrequest_time), sent_authrequest_serial(Sent_authrequest_serial), node_capabilities(Node_capabilities), revoked_auth(Revoked_auth), added_in_shared_group(Added_in_shared_group), in_shared_group(In_shared_group), stack_version(Stack_version), offline_authreq_id(Offline_authreq_id), node_capabilities_and(Node_capabilities_and), authreq_crc(Authreq_crc), authreq_src(Authreq_src), pop_score(Pop_score), main_phone(Main_phone), unified_servants(Unified_servants), phone_home_normalized(Phone_home_normalized), phone_office_normalized(Phone_office_normalized), phone_mobile_normalized(Phone_mobile_normalized), sent_authrequest_initmethod(Sent_authrequest_initmethod), authreq_initmethod(Authreq_initmethod), sent_authrequest_extrasbitmask(Sent_authrequest_extrasbitmask) {
    defaults();
}
Contacts::Contacts(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), is_permanent(Is_permanent), skypename(Skypename), pstnnumber(Pstnnumber), aliases(Aliases), fullname(Fullname), birthday(Birthday), gender(Gender), languages(Languages), country(Country), province(Province), city(City), phone_home(Phone_home), phone_office(Phone_office), phone_mobile(Phone_mobile), emails(Emails), homepage(Homepage), about(About), mood_text(Mood_text), rich_mood_text(Rich_mood_text), timezone(Timezone), profile_timestamp(Profile_timestamp), nrof_authed_buddies(Nrof_authed_buddies), ipcountry(Ipcountry), avatar_timestamp(Avatar_timestamp), mood_timestamp(Mood_timestamp), received_authrequest(Received_authrequest), authreq_timestamp(Authreq_timestamp), lastonline_timestamp(Lastonline_timestamp), availability(Availability), displayname(Displayname), refreshing(Refreshing), given_authlevel(Given_authlevel), given_displayname(Given_displayname), assigned_speeddial(Assigned_speeddial), assigned_comment(Assigned_comment), alertstring(Alertstring), lastused_timestamp(Lastused_timestamp), authrequest_count(Authrequest_count), assigned_phone1(Assigned_phone1), assigned_phone1_label(Assigned_phone1_label), assigned_phone2(Assigned_phone2), assigned_phone2_label(Assigned_phone2_label), assigned_phone3(Assigned_phone3), assigned_phone3_label(Assigned_phone3_label), buddystatus(Buddystatus), isauthorized(Isauthorized), popularity_ord(Popularity_ord), isblocked(Isblocked), certificate_send_count(Certificate_send_count), account_modification_serial_nr(Account_modification_serial_nr), nr_of_buddies(Nr_of_buddies), server_synced(Server_synced), contactlist_track(Contactlist_track), last_used_networktime(Last_used_networktime), authorized_time(Authorized_time), sent_authrequest(Sent_authrequest), sent_authrequest_time(Sent_authrequest_time), sent_authrequest_serial(Sent_authrequest_serial), node_capabilities(Node_capabilities), revoked_auth(Revoked_auth), added_in_shared_group(Added_in_shared_group), in_shared_group(In_shared_group), stack_version(Stack_version), offline_authreq_id(Offline_authreq_id), node_capabilities_and(Node_capabilities_and), authreq_crc(Authreq_crc), authreq_src(Authreq_src), pop_score(Pop_score), main_phone(Main_phone), unified_servants(Unified_servants), phone_home_normalized(Phone_home_normalized), phone_office_normalized(Phone_office_normalized), phone_mobile_normalized(Phone_mobile_normalized), sent_authrequest_initmethod(Sent_authrequest_initmethod), authreq_initmethod(Authreq_initmethod), sent_authrequest_extrasbitmask(Sent_authrequest_extrasbitmask) {
    defaults();
    size_t size = (rec.size() > 77) ? 77 : rec.size();
    switch(size) {
    case 77: sent_authrequest_extrasbitmask = convert<const std::string&, int>(rec[76]);
        sent_authrequest_extrasbitmask.setModified(false);
    case 76: authreq_initmethod = convert<const std::string&, int>(rec[75]);
        authreq_initmethod.setModified(false);
    case 75: sent_authrequest_initmethod = convert<const std::string&, int>(rec[74]);
        sent_authrequest_initmethod.setModified(false);
    case 74: phone_mobile_normalized = convert<const std::string&, std::string>(rec[73]);
        phone_mobile_normalized.setModified(false);
    case 73: phone_office_normalized = convert<const std::string&, std::string>(rec[72]);
        phone_office_normalized.setModified(false);
    case 72: phone_home_normalized = convert<const std::string&, std::string>(rec[71]);
        phone_home_normalized.setModified(false);
    case 71: unified_servants = convert<const std::string&, std::string>(rec[70]);
        unified_servants.setModified(false);
    case 70: main_phone = convert<const std::string&, std::string>(rec[69]);
        main_phone.setModified(false);
    case 69: pop_score = convert<const std::string&, int>(rec[68]);
        pop_score.setModified(false);
    case 68: authreq_src = convert<const std::string&, int>(rec[67]);
        authreq_src.setModified(false);
    case 67: authreq_crc = convert<const std::string&, int>(rec[66]);
        authreq_crc.setModified(false);
    case 66: node_capabilities_and = convert<const std::string&, int>(rec[65]);
        node_capabilities_and.setModified(false);
    case 65: offline_authreq_id = convert<const std::string&, int>(rec[64]);
        offline_authreq_id.setModified(false);
    case 64: stack_version = convert<const std::string&, int>(rec[63]);
        stack_version.setModified(false);
    case 63: in_shared_group = convert<const std::string&, int>(rec[62]);
        in_shared_group.setModified(false);
    case 62: added_in_shared_group = convert<const std::string&, int>(rec[61]);
        added_in_shared_group.setModified(false);
    case 61: revoked_auth = convert<const std::string&, int>(rec[60]);
        revoked_auth.setModified(false);
    case 60: node_capabilities = convert<const std::string&, int>(rec[59]);
        node_capabilities.setModified(false);
    case 59: sent_authrequest_serial = convert<const std::string&, int>(rec[58]);
        sent_authrequest_serial.setModified(false);
    case 58: sent_authrequest_time = convert<const std::string&, int>(rec[57]);
        sent_authrequest_time.setModified(false);
    case 57: sent_authrequest = convert<const std::string&, std::string>(rec[56]);
        sent_authrequest.setModified(false);
    case 56: authorized_time = convert<const std::string&, int>(rec[55]);
        authorized_time.setModified(false);
    case 55: last_used_networktime = convert<const std::string&, int>(rec[54]);
        last_used_networktime.setModified(false);
    case 54: contactlist_track = convert<const std::string&, int>(rec[53]);
        contactlist_track.setModified(false);
    case 53: server_synced = convert<const std::string&, int>(rec[52]);
        server_synced.setModified(false);
    case 52: nr_of_buddies = convert<const std::string&, int>(rec[51]);
        nr_of_buddies.setModified(false);
    case 51: account_modification_serial_nr = convert<const std::string&, int>(rec[50]);
        account_modification_serial_nr.setModified(false);
    case 50: certificate_send_count = convert<const std::string&, int>(rec[49]);
        certificate_send_count.setModified(false);
    case 49: isblocked = convert<const std::string&, int>(rec[48]);
        isblocked.setModified(false);
    case 48: popularity_ord = convert<const std::string&, int>(rec[47]);
        popularity_ord.setModified(false);
    case 47: isauthorized = convert<const std::string&, int>(rec[46]);
        isauthorized.setModified(false);
    case 46: buddystatus = convert<const std::string&, int>(rec[45]);
        buddystatus.setModified(false);
    case 45: assigned_phone3_label = convert<const std::string&, std::string>(rec[44]);
        assigned_phone3_label.setModified(false);
    case 44: assigned_phone3 = convert<const std::string&, std::string>(rec[43]);
        assigned_phone3.setModified(false);
    case 43: assigned_phone2_label = convert<const std::string&, std::string>(rec[42]);
        assigned_phone2_label.setModified(false);
    case 42: assigned_phone2 = convert<const std::string&, std::string>(rec[41]);
        assigned_phone2.setModified(false);
    case 41: assigned_phone1_label = convert<const std::string&, std::string>(rec[40]);
        assigned_phone1_label.setModified(false);
    case 40: assigned_phone1 = convert<const std::string&, std::string>(rec[39]);
        assigned_phone1.setModified(false);
    case 39: authrequest_count = convert<const std::string&, int>(rec[38]);
        authrequest_count.setModified(false);
    case 38: lastused_timestamp = convert<const std::string&, int>(rec[37]);
        lastused_timestamp.setModified(false);
    case 37: alertstring = convert<const std::string&, std::string>(rec[36]);
        alertstring.setModified(false);
    case 36: assigned_comment = convert<const std::string&, std::string>(rec[35]);
        assigned_comment.setModified(false);
    case 35: assigned_speeddial = convert<const std::string&, std::string>(rec[34]);
        assigned_speeddial.setModified(false);
    case 34: given_displayname = convert<const std::string&, std::string>(rec[33]);
        given_displayname.setModified(false);
    case 33: given_authlevel = convert<const std::string&, int>(rec[32]);
        given_authlevel.setModified(false);
    case 32: refreshing = convert<const std::string&, int>(rec[31]);
        refreshing.setModified(false);
    case 31: displayname = convert<const std::string&, std::string>(rec[30]);
        displayname.setModified(false);
    case 30: availability = convert<const std::string&, int>(rec[29]);
        availability.setModified(false);
    case 29: lastonline_timestamp = convert<const std::string&, int>(rec[28]);
        lastonline_timestamp.setModified(false);
    case 28: authreq_timestamp = convert<const std::string&, int>(rec[27]);
        authreq_timestamp.setModified(false);
    case 27: received_authrequest = convert<const std::string&, std::string>(rec[26]);
        received_authrequest.setModified(false);
    case 26: mood_timestamp = convert<const std::string&, int>(rec[25]);
        mood_timestamp.setModified(false);
    case 25: avatar_timestamp = convert<const std::string&, int>(rec[24]);
        avatar_timestamp.setModified(false);
    case 24: ipcountry = convert<const std::string&, std::string>(rec[23]);
        ipcountry.setModified(false);
    case 23: nrof_authed_buddies = convert<const std::string&, int>(rec[22]);
        nrof_authed_buddies.setModified(false);
    case 22: profile_timestamp = convert<const std::string&, int>(rec[21]);
        profile_timestamp.setModified(false);
    case 21: timezone = convert<const std::string&, int>(rec[20]);
        timezone.setModified(false);
    case 20: rich_mood_text = convert<const std::string&, std::string>(rec[19]);
        rich_mood_text.setModified(false);
    case 19: mood_text = convert<const std::string&, std::string>(rec[18]);
        mood_text.setModified(false);
    case 18: about = convert<const std::string&, std::string>(rec[17]);
        about.setModified(false);
    case 17: homepage = convert<const std::string&, std::string>(rec[16]);
        homepage.setModified(false);
    case 16: emails = convert<const std::string&, std::string>(rec[15]);
        emails.setModified(false);
    case 15: phone_mobile = convert<const std::string&, std::string>(rec[14]);
        phone_mobile.setModified(false);
    case 14: phone_office = convert<const std::string&, std::string>(rec[13]);
        phone_office.setModified(false);
    case 13: phone_home = convert<const std::string&, std::string>(rec[12]);
        phone_home.setModified(false);
    case 12: city = convert<const std::string&, std::string>(rec[11]);
        city.setModified(false);
    case 11: province = convert<const std::string&, std::string>(rec[10]);
        province.setModified(false);
    case 10: country = convert<const std::string&, std::string>(rec[9]);
        country.setModified(false);
    case 9: languages = convert<const std::string&, std::string>(rec[8]);
        languages.setModified(false);
    case 8: gender = convert<const std::string&, int>(rec[7]);
        gender.setModified(false);
    case 7: birthday = convert<const std::string&, int>(rec[6]);
        birthday.setModified(false);
    case 6: fullname = convert<const std::string&, std::string>(rec[5]);
        fullname.setModified(false);
    case 5: aliases = convert<const std::string&, std::string>(rec[4]);
        aliases.setModified(false);
    case 4: pstnnumber = convert<const std::string&, std::string>(rec[3]);
        pstnnumber.setModified(false);
    case 3: skypename = convert<const std::string&, std::string>(rec[2]);
        skypename.setModified(false);
    case 2: is_permanent = convert<const std::string&, int>(rec[1]);
        is_permanent.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Contacts::Contacts(const Contacts& obj)
     : litesql::Persistent(obj), id(obj.id), is_permanent(obj.is_permanent), skypename(obj.skypename), pstnnumber(obj.pstnnumber), aliases(obj.aliases), fullname(obj.fullname), birthday(obj.birthday), gender(obj.gender), languages(obj.languages), country(obj.country), province(obj.province), city(obj.city), phone_home(obj.phone_home), phone_office(obj.phone_office), phone_mobile(obj.phone_mobile), emails(obj.emails), homepage(obj.homepage), about(obj.about), mood_text(obj.mood_text), rich_mood_text(obj.rich_mood_text), timezone(obj.timezone), profile_timestamp(obj.profile_timestamp), nrof_authed_buddies(obj.nrof_authed_buddies), ipcountry(obj.ipcountry), avatar_timestamp(obj.avatar_timestamp), mood_timestamp(obj.mood_timestamp), received_authrequest(obj.received_authrequest), authreq_timestamp(obj.authreq_timestamp), lastonline_timestamp(obj.lastonline_timestamp), availability(obj.availability), displayname(obj.displayname), refreshing(obj.refreshing), given_authlevel(obj.given_authlevel), given_displayname(obj.given_displayname), assigned_speeddial(obj.assigned_speeddial), assigned_comment(obj.assigned_comment), alertstring(obj.alertstring), lastused_timestamp(obj.lastused_timestamp), authrequest_count(obj.authrequest_count), assigned_phone1(obj.assigned_phone1), assigned_phone1_label(obj.assigned_phone1_label), assigned_phone2(obj.assigned_phone2), assigned_phone2_label(obj.assigned_phone2_label), assigned_phone3(obj.assigned_phone3), assigned_phone3_label(obj.assigned_phone3_label), buddystatus(obj.buddystatus), isauthorized(obj.isauthorized), popularity_ord(obj.popularity_ord), isblocked(obj.isblocked), certificate_send_count(obj.certificate_send_count), account_modification_serial_nr(obj.account_modification_serial_nr), nr_of_buddies(obj.nr_of_buddies), server_synced(obj.server_synced), contactlist_track(obj.contactlist_track), last_used_networktime(obj.last_used_networktime), authorized_time(obj.authorized_time), sent_authrequest(obj.sent_authrequest), sent_authrequest_time(obj.sent_authrequest_time), sent_authrequest_serial(obj.sent_authrequest_serial), node_capabilities(obj.node_capabilities), revoked_auth(obj.revoked_auth), added_in_shared_group(obj.added_in_shared_group), in_shared_group(obj.in_shared_group), stack_version(obj.stack_version), offline_authreq_id(obj.offline_authreq_id), node_capabilities_and(obj.node_capabilities_and), authreq_crc(obj.authreq_crc), authreq_src(obj.authreq_src), pop_score(obj.pop_score), main_phone(obj.main_phone), unified_servants(obj.unified_servants), phone_home_normalized(obj.phone_home_normalized), phone_office_normalized(obj.phone_office_normalized), phone_mobile_normalized(obj.phone_mobile_normalized), sent_authrequest_initmethod(obj.sent_authrequest_initmethod), authreq_initmethod(obj.authreq_initmethod), sent_authrequest_extrasbitmask(obj.sent_authrequest_extrasbitmask) {
}
const Contacts& Contacts::operator=(const Contacts& obj) {
    if (this != &obj) {
        id = obj.id;
        is_permanent = obj.is_permanent;
        skypename = obj.skypename;
        pstnnumber = obj.pstnnumber;
        aliases = obj.aliases;
        fullname = obj.fullname;
        birthday = obj.birthday;
        gender = obj.gender;
        languages = obj.languages;
        country = obj.country;
        province = obj.province;
        city = obj.city;
        phone_home = obj.phone_home;
        phone_office = obj.phone_office;
        phone_mobile = obj.phone_mobile;
        emails = obj.emails;
        homepage = obj.homepage;
        about = obj.about;
        mood_text = obj.mood_text;
        rich_mood_text = obj.rich_mood_text;
        timezone = obj.timezone;
        profile_timestamp = obj.profile_timestamp;
        nrof_authed_buddies = obj.nrof_authed_buddies;
        ipcountry = obj.ipcountry;
        avatar_timestamp = obj.avatar_timestamp;
        mood_timestamp = obj.mood_timestamp;
        received_authrequest = obj.received_authrequest;
        authreq_timestamp = obj.authreq_timestamp;
        lastonline_timestamp = obj.lastonline_timestamp;
        availability = obj.availability;
        displayname = obj.displayname;
        refreshing = obj.refreshing;
        given_authlevel = obj.given_authlevel;
        given_displayname = obj.given_displayname;
        assigned_speeddial = obj.assigned_speeddial;
        assigned_comment = obj.assigned_comment;
        alertstring = obj.alertstring;
        lastused_timestamp = obj.lastused_timestamp;
        authrequest_count = obj.authrequest_count;
        assigned_phone1 = obj.assigned_phone1;
        assigned_phone1_label = obj.assigned_phone1_label;
        assigned_phone2 = obj.assigned_phone2;
        assigned_phone2_label = obj.assigned_phone2_label;
        assigned_phone3 = obj.assigned_phone3;
        assigned_phone3_label = obj.assigned_phone3_label;
        buddystatus = obj.buddystatus;
        isauthorized = obj.isauthorized;
        popularity_ord = obj.popularity_ord;
        isblocked = obj.isblocked;
        certificate_send_count = obj.certificate_send_count;
        account_modification_serial_nr = obj.account_modification_serial_nr;
        nr_of_buddies = obj.nr_of_buddies;
        server_synced = obj.server_synced;
        contactlist_track = obj.contactlist_track;
        last_used_networktime = obj.last_used_networktime;
        authorized_time = obj.authorized_time;
        sent_authrequest = obj.sent_authrequest;
        sent_authrequest_time = obj.sent_authrequest_time;
        sent_authrequest_serial = obj.sent_authrequest_serial;
        node_capabilities = obj.node_capabilities;
        revoked_auth = obj.revoked_auth;
        added_in_shared_group = obj.added_in_shared_group;
        in_shared_group = obj.in_shared_group;
        stack_version = obj.stack_version;
        offline_authreq_id = obj.offline_authreq_id;
        node_capabilities_and = obj.node_capabilities_and;
        authreq_crc = obj.authreq_crc;
        authreq_src = obj.authreq_src;
        pop_score = obj.pop_score;
        main_phone = obj.main_phone;
        unified_servants = obj.unified_servants;
        phone_home_normalized = obj.phone_home_normalized;
        phone_office_normalized = obj.phone_office_normalized;
        phone_mobile_normalized = obj.phone_mobile_normalized;
        sent_authrequest_initmethod = obj.sent_authrequest_initmethod;
        authreq_initmethod = obj.authreq_initmethod;
        sent_authrequest_extrasbitmask = obj.sent_authrequest_extrasbitmask;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string Contacts::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(is_permanent.name());
    values.push_back(is_permanent);
    is_permanent.setModified(false);
    fields.push_back(skypename.name());
    values.push_back(skypename);
    skypename.setModified(false);
    fields.push_back(pstnnumber.name());
    values.push_back(pstnnumber);
    pstnnumber.setModified(false);
    fields.push_back(aliases.name());
    values.push_back(aliases);
    aliases.setModified(false);
    fields.push_back(fullname.name());
    values.push_back(fullname);
    fullname.setModified(false);
    fields.push_back(birthday.name());
    values.push_back(birthday);
    birthday.setModified(false);
    fields.push_back(gender.name());
    values.push_back(gender);
    gender.setModified(false);
    fields.push_back(languages.name());
    values.push_back(languages);
    languages.setModified(false);
    fields.push_back(country.name());
    values.push_back(country);
    country.setModified(false);
    fields.push_back(province.name());
    values.push_back(province);
    province.setModified(false);
    fields.push_back(city.name());
    values.push_back(city);
    city.setModified(false);
    fields.push_back(phone_home.name());
    values.push_back(phone_home);
    phone_home.setModified(false);
    fields.push_back(phone_office.name());
    values.push_back(phone_office);
    phone_office.setModified(false);
    fields.push_back(phone_mobile.name());
    values.push_back(phone_mobile);
    phone_mobile.setModified(false);
    fields.push_back(emails.name());
    values.push_back(emails);
    emails.setModified(false);
    fields.push_back(homepage.name());
    values.push_back(homepage);
    homepage.setModified(false);
    fields.push_back(about.name());
    values.push_back(about);
    about.setModified(false);
    fields.push_back(mood_text.name());
    values.push_back(mood_text);
    mood_text.setModified(false);
    fields.push_back(rich_mood_text.name());
    values.push_back(rich_mood_text);
    rich_mood_text.setModified(false);
    fields.push_back(timezone.name());
    values.push_back(timezone);
    timezone.setModified(false);
    fields.push_back(profile_timestamp.name());
    values.push_back(profile_timestamp);
    profile_timestamp.setModified(false);
    fields.push_back(nrof_authed_buddies.name());
    values.push_back(nrof_authed_buddies);
    nrof_authed_buddies.setModified(false);
    fields.push_back(ipcountry.name());
    values.push_back(ipcountry);
    ipcountry.setModified(false);
    fields.push_back(avatar_timestamp.name());
    values.push_back(avatar_timestamp);
    avatar_timestamp.setModified(false);
    fields.push_back(mood_timestamp.name());
    values.push_back(mood_timestamp);
    mood_timestamp.setModified(false);
    fields.push_back(received_authrequest.name());
    values.push_back(received_authrequest);
    received_authrequest.setModified(false);
    fields.push_back(authreq_timestamp.name());
    values.push_back(authreq_timestamp);
    authreq_timestamp.setModified(false);
    fields.push_back(lastonline_timestamp.name());
    values.push_back(lastonline_timestamp);
    lastonline_timestamp.setModified(false);
    fields.push_back(availability.name());
    values.push_back(availability);
    availability.setModified(false);
    fields.push_back(displayname.name());
    values.push_back(displayname);
    displayname.setModified(false);
    fields.push_back(refreshing.name());
    values.push_back(refreshing);
    refreshing.setModified(false);
    fields.push_back(given_authlevel.name());
    values.push_back(given_authlevel);
    given_authlevel.setModified(false);
    fields.push_back(given_displayname.name());
    values.push_back(given_displayname);
    given_displayname.setModified(false);
    fields.push_back(assigned_speeddial.name());
    values.push_back(assigned_speeddial);
    assigned_speeddial.setModified(false);
    fields.push_back(assigned_comment.name());
    values.push_back(assigned_comment);
    assigned_comment.setModified(false);
    fields.push_back(alertstring.name());
    values.push_back(alertstring);
    alertstring.setModified(false);
    fields.push_back(lastused_timestamp.name());
    values.push_back(lastused_timestamp);
    lastused_timestamp.setModified(false);
    fields.push_back(authrequest_count.name());
    values.push_back(authrequest_count);
    authrequest_count.setModified(false);
    fields.push_back(assigned_phone1.name());
    values.push_back(assigned_phone1);
    assigned_phone1.setModified(false);
    fields.push_back(assigned_phone1_label.name());
    values.push_back(assigned_phone1_label);
    assigned_phone1_label.setModified(false);
    fields.push_back(assigned_phone2.name());
    values.push_back(assigned_phone2);
    assigned_phone2.setModified(false);
    fields.push_back(assigned_phone2_label.name());
    values.push_back(assigned_phone2_label);
    assigned_phone2_label.setModified(false);
    fields.push_back(assigned_phone3.name());
    values.push_back(assigned_phone3);
    assigned_phone3.setModified(false);
    fields.push_back(assigned_phone3_label.name());
    values.push_back(assigned_phone3_label);
    assigned_phone3_label.setModified(false);
    fields.push_back(buddystatus.name());
    values.push_back(buddystatus);
    buddystatus.setModified(false);
    fields.push_back(isauthorized.name());
    values.push_back(isauthorized);
    isauthorized.setModified(false);
    fields.push_back(popularity_ord.name());
    values.push_back(popularity_ord);
    popularity_ord.setModified(false);
    fields.push_back(isblocked.name());
    values.push_back(isblocked);
    isblocked.setModified(false);
    fields.push_back(certificate_send_count.name());
    values.push_back(certificate_send_count);
    certificate_send_count.setModified(false);
    fields.push_back(account_modification_serial_nr.name());
    values.push_back(account_modification_serial_nr);
    account_modification_serial_nr.setModified(false);
    fields.push_back(nr_of_buddies.name());
    values.push_back(nr_of_buddies);
    nr_of_buddies.setModified(false);
    fields.push_back(server_synced.name());
    values.push_back(server_synced);
    server_synced.setModified(false);
    fields.push_back(contactlist_track.name());
    values.push_back(contactlist_track);
    contactlist_track.setModified(false);
    fields.push_back(last_used_networktime.name());
    values.push_back(last_used_networktime);
    last_used_networktime.setModified(false);
    fields.push_back(authorized_time.name());
    values.push_back(authorized_time);
    authorized_time.setModified(false);
    fields.push_back(sent_authrequest.name());
    values.push_back(sent_authrequest);
    sent_authrequest.setModified(false);
    fields.push_back(sent_authrequest_time.name());
    values.push_back(sent_authrequest_time);
    sent_authrequest_time.setModified(false);
    fields.push_back(sent_authrequest_serial.name());
    values.push_back(sent_authrequest_serial);
    sent_authrequest_serial.setModified(false);
    fields.push_back(node_capabilities.name());
    values.push_back(node_capabilities);
    node_capabilities.setModified(false);
    fields.push_back(revoked_auth.name());
    values.push_back(revoked_auth);
    revoked_auth.setModified(false);
    fields.push_back(added_in_shared_group.name());
    values.push_back(added_in_shared_group);
    added_in_shared_group.setModified(false);
    fields.push_back(in_shared_group.name());
    values.push_back(in_shared_group);
    in_shared_group.setModified(false);
    fields.push_back(stack_version.name());
    values.push_back(stack_version);
    stack_version.setModified(false);
    fields.push_back(offline_authreq_id.name());
    values.push_back(offline_authreq_id);
    offline_authreq_id.setModified(false);
    fields.push_back(node_capabilities_and.name());
    values.push_back(node_capabilities_and);
    node_capabilities_and.setModified(false);
    fields.push_back(authreq_crc.name());
    values.push_back(authreq_crc);
    authreq_crc.setModified(false);
    fields.push_back(authreq_src.name());
    values.push_back(authreq_src);
    authreq_src.setModified(false);
    fields.push_back(pop_score.name());
    values.push_back(pop_score);
    pop_score.setModified(false);
    fields.push_back(main_phone.name());
    values.push_back(main_phone);
    main_phone.setModified(false);
    fields.push_back(unified_servants.name());
    values.push_back(unified_servants);
    unified_servants.setModified(false);
    fields.push_back(phone_home_normalized.name());
    values.push_back(phone_home_normalized);
    phone_home_normalized.setModified(false);
    fields.push_back(phone_office_normalized.name());
    values.push_back(phone_office_normalized);
    phone_office_normalized.setModified(false);
    fields.push_back(phone_mobile_normalized.name());
    values.push_back(phone_mobile_normalized);
    phone_mobile_normalized.setModified(false);
    fields.push_back(sent_authrequest_initmethod.name());
    values.push_back(sent_authrequest_initmethod);
    sent_authrequest_initmethod.setModified(false);
    fields.push_back(authreq_initmethod.name());
    values.push_back(authreq_initmethod);
    authreq_initmethod.setModified(false);
    fields.push_back(sent_authrequest_extrasbitmask.name());
    values.push_back(sent_authrequest_extrasbitmask);
    sent_authrequest_extrasbitmask.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Contacts::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    //Type processing disabled
    //type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Contacts::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, is_permanent);
    updateField(updates, table__, skypename);
    updateField(updates, table__, pstnnumber);
    updateField(updates, table__, aliases);
    updateField(updates, table__, fullname);
    updateField(updates, table__, birthday);
    updateField(updates, table__, gender);
    updateField(updates, table__, languages);
    updateField(updates, table__, country);
    updateField(updates, table__, province);
    updateField(updates, table__, city);
    updateField(updates, table__, phone_home);
    updateField(updates, table__, phone_office);
    updateField(updates, table__, phone_mobile);
    updateField(updates, table__, emails);
    updateField(updates, table__, homepage);
    updateField(updates, table__, about);
    updateField(updates, table__, mood_text);
    updateField(updates, table__, rich_mood_text);
    updateField(updates, table__, timezone);
    updateField(updates, table__, profile_timestamp);
    updateField(updates, table__, nrof_authed_buddies);
    updateField(updates, table__, ipcountry);
    updateField(updates, table__, avatar_timestamp);
    updateField(updates, table__, mood_timestamp);
    updateField(updates, table__, received_authrequest);
    updateField(updates, table__, authreq_timestamp);
    updateField(updates, table__, lastonline_timestamp);
    updateField(updates, table__, availability);
    updateField(updates, table__, displayname);
    updateField(updates, table__, refreshing);
    updateField(updates, table__, given_authlevel);
    updateField(updates, table__, given_displayname);
    updateField(updates, table__, assigned_speeddial);
    updateField(updates, table__, assigned_comment);
    updateField(updates, table__, alertstring);
    updateField(updates, table__, lastused_timestamp);
    updateField(updates, table__, authrequest_count);
    updateField(updates, table__, assigned_phone1);
    updateField(updates, table__, assigned_phone1_label);
    updateField(updates, table__, assigned_phone2);
    updateField(updates, table__, assigned_phone2_label);
    updateField(updates, table__, assigned_phone3);
    updateField(updates, table__, assigned_phone3_label);
    updateField(updates, table__, buddystatus);
    updateField(updates, table__, isauthorized);
    updateField(updates, table__, popularity_ord);
    updateField(updates, table__, isblocked);
    updateField(updates, table__, certificate_send_count);
    updateField(updates, table__, account_modification_serial_nr);
    updateField(updates, table__, nr_of_buddies);
    updateField(updates, table__, server_synced);
    updateField(updates, table__, contactlist_track);
    updateField(updates, table__, last_used_networktime);
    updateField(updates, table__, authorized_time);
    updateField(updates, table__, sent_authrequest);
    updateField(updates, table__, sent_authrequest_time);
    updateField(updates, table__, sent_authrequest_serial);
    updateField(updates, table__, node_capabilities);
    updateField(updates, table__, revoked_auth);
    updateField(updates, table__, added_in_shared_group);
    updateField(updates, table__, in_shared_group);
    updateField(updates, table__, stack_version);
    updateField(updates, table__, offline_authreq_id);
    updateField(updates, table__, node_capabilities_and);
    updateField(updates, table__, authreq_crc);
    updateField(updates, table__, authreq_src);
    updateField(updates, table__, pop_score);
    updateField(updates, table__, main_phone);
    updateField(updates, table__, unified_servants);
    updateField(updates, table__, phone_home_normalized);
    updateField(updates, table__, phone_office_normalized);
    updateField(updates, table__, phone_mobile_normalized);
    updateField(updates, table__, sent_authrequest_initmethod);
    updateField(updates, table__, authreq_initmethod);
    updateField(updates, table__, sent_authrequest_extrasbitmask);
}
void Contacts::addIDUpdates(Updates& updates) {
}
void Contacts::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Is_permanent);
    ftypes.push_back(Skypename);
    ftypes.push_back(Pstnnumber);
    ftypes.push_back(Aliases);
    ftypes.push_back(Fullname);
    ftypes.push_back(Birthday);
    ftypes.push_back(Gender);
    ftypes.push_back(Languages);
    ftypes.push_back(Country);
    ftypes.push_back(Province);
    ftypes.push_back(City);
    ftypes.push_back(Phone_home);
    ftypes.push_back(Phone_office);
    ftypes.push_back(Phone_mobile);
    ftypes.push_back(Emails);
    ftypes.push_back(Homepage);
    ftypes.push_back(About);
    ftypes.push_back(Mood_text);
    ftypes.push_back(Rich_mood_text);
    ftypes.push_back(Timezone);
    ftypes.push_back(Profile_timestamp);
    ftypes.push_back(Nrof_authed_buddies);
    ftypes.push_back(Ipcountry);
    ftypes.push_back(Avatar_timestamp);
    ftypes.push_back(Mood_timestamp);
    ftypes.push_back(Received_authrequest);
    ftypes.push_back(Authreq_timestamp);
    ftypes.push_back(Lastonline_timestamp);
    ftypes.push_back(Availability);
    ftypes.push_back(Displayname);
    ftypes.push_back(Refreshing);
    ftypes.push_back(Given_authlevel);
    ftypes.push_back(Given_displayname);
    ftypes.push_back(Assigned_speeddial);
    ftypes.push_back(Assigned_comment);
    ftypes.push_back(Alertstring);
    ftypes.push_back(Lastused_timestamp);
    ftypes.push_back(Authrequest_count);
    ftypes.push_back(Assigned_phone1);
    ftypes.push_back(Assigned_phone1_label);
    ftypes.push_back(Assigned_phone2);
    ftypes.push_back(Assigned_phone2_label);
    ftypes.push_back(Assigned_phone3);
    ftypes.push_back(Assigned_phone3_label);
    ftypes.push_back(Buddystatus);
    ftypes.push_back(Isauthorized);
    ftypes.push_back(Popularity_ord);
    ftypes.push_back(Isblocked);
    ftypes.push_back(Certificate_send_count);
    ftypes.push_back(Account_modification_serial_nr);
    ftypes.push_back(Nr_of_buddies);
    ftypes.push_back(Server_synced);
    ftypes.push_back(Contactlist_track);
    ftypes.push_back(Last_used_networktime);
    ftypes.push_back(Authorized_time);
    ftypes.push_back(Sent_authrequest);
    ftypes.push_back(Sent_authrequest_time);
    ftypes.push_back(Sent_authrequest_serial);
    ftypes.push_back(Node_capabilities);
    ftypes.push_back(Revoked_auth);
    ftypes.push_back(Added_in_shared_group);
    ftypes.push_back(In_shared_group);
    ftypes.push_back(Stack_version);
    ftypes.push_back(Offline_authreq_id);
    ftypes.push_back(Node_capabilities_and);
    ftypes.push_back(Authreq_crc);
    ftypes.push_back(Authreq_src);
    ftypes.push_back(Pop_score);
    ftypes.push_back(Main_phone);
    ftypes.push_back(Unified_servants);
    ftypes.push_back(Phone_home_normalized);
    ftypes.push_back(Phone_office_normalized);
    ftypes.push_back(Phone_mobile_normalized);
    ftypes.push_back(Sent_authrequest_initmethod);
    ftypes.push_back(Authreq_initmethod);
    ftypes.push_back(Sent_authrequest_extrasbitmask);
}
void Contacts::delRecord() {
    deleteFromTable(table__, id);
}
void Contacts::delRelations() {
}
void Contacts::update() {
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
void Contacts::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<Contacts> p(upcastCopy());
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
bool Contacts::typeIsCorrect() const {
    return true;
}
std::unique_ptr<Contacts> Contacts::upcast() const {
    return unique_ptr<Contacts>(new Contacts(*this));
}
std::unique_ptr<Contacts> Contacts::upcastCopy() const {
    Contacts* np = new Contacts(*this);
    np->id = id;
    np->is_permanent = is_permanent;
    np->skypename = skypename;
    np->pstnnumber = pstnnumber;
    np->aliases = aliases;
    np->fullname = fullname;
    np->birthday = birthday;
    np->gender = gender;
    np->languages = languages;
    np->country = country;
    np->province = province;
    np->city = city;
    np->phone_home = phone_home;
    np->phone_office = phone_office;
    np->phone_mobile = phone_mobile;
    np->emails = emails;
    np->homepage = homepage;
    np->about = about;
    np->mood_text = mood_text;
    np->rich_mood_text = rich_mood_text;
    np->timezone = timezone;
    np->profile_timestamp = profile_timestamp;
    np->nrof_authed_buddies = nrof_authed_buddies;
    np->ipcountry = ipcountry;
    np->avatar_timestamp = avatar_timestamp;
    np->mood_timestamp = mood_timestamp;
    np->received_authrequest = received_authrequest;
    np->authreq_timestamp = authreq_timestamp;
    np->lastonline_timestamp = lastonline_timestamp;
    np->availability = availability;
    np->displayname = displayname;
    np->refreshing = refreshing;
    np->given_authlevel = given_authlevel;
    np->given_displayname = given_displayname;
    np->assigned_speeddial = assigned_speeddial;
    np->assigned_comment = assigned_comment;
    np->alertstring = alertstring;
    np->lastused_timestamp = lastused_timestamp;
    np->authrequest_count = authrequest_count;
    np->assigned_phone1 = assigned_phone1;
    np->assigned_phone1_label = assigned_phone1_label;
    np->assigned_phone2 = assigned_phone2;
    np->assigned_phone2_label = assigned_phone2_label;
    np->assigned_phone3 = assigned_phone3;
    np->assigned_phone3_label = assigned_phone3_label;
    np->buddystatus = buddystatus;
    np->isauthorized = isauthorized;
    np->popularity_ord = popularity_ord;
    np->isblocked = isblocked;
    np->certificate_send_count = certificate_send_count;
    np->account_modification_serial_nr = account_modification_serial_nr;
    np->nr_of_buddies = nr_of_buddies;
    np->server_synced = server_synced;
    np->contactlist_track = contactlist_track;
    np->last_used_networktime = last_used_networktime;
    np->authorized_time = authorized_time;
    np->sent_authrequest = sent_authrequest;
    np->sent_authrequest_time = sent_authrequest_time;
    np->sent_authrequest_serial = sent_authrequest_serial;
    np->node_capabilities = node_capabilities;
    np->revoked_auth = revoked_auth;
    np->added_in_shared_group = added_in_shared_group;
    np->in_shared_group = in_shared_group;
    np->stack_version = stack_version;
    np->offline_authreq_id = offline_authreq_id;
    np->node_capabilities_and = node_capabilities_and;
    np->authreq_crc = authreq_crc;
    np->authreq_src = authreq_src;
    np->pop_score = pop_score;
    np->main_phone = main_phone;
    np->unified_servants = unified_servants;
    np->phone_home_normalized = phone_home_normalized;
    np->phone_office_normalized = phone_office_normalized;
    np->phone_mobile_normalized = phone_mobile_normalized;
    np->sent_authrequest_initmethod = sent_authrequest_initmethod;
    np->authreq_initmethod = authreq_initmethod;
    np->sent_authrequest_extrasbitmask = sent_authrequest_extrasbitmask;
    np->inDatabase = inDatabase;
    return unique_ptr<Contacts>(np);
}
std::ostream & operator<<(std::ostream& os, Contacts o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.is_permanent.name() << " = " << o.is_permanent << std::endl;
    os << o.skypename.name() << " = " << o.skypename << std::endl;
    os << o.pstnnumber.name() << " = " << o.pstnnumber << std::endl;
    os << o.aliases.name() << " = " << o.aliases << std::endl;
    os << o.fullname.name() << " = " << o.fullname << std::endl;
    os << o.birthday.name() << " = " << o.birthday << std::endl;
    os << o.gender.name() << " = " << o.gender << std::endl;
    os << o.languages.name() << " = " << o.languages << std::endl;
    os << o.country.name() << " = " << o.country << std::endl;
    os << o.province.name() << " = " << o.province << std::endl;
    os << o.city.name() << " = " << o.city << std::endl;
    os << o.phone_home.name() << " = " << o.phone_home << std::endl;
    os << o.phone_office.name() << " = " << o.phone_office << std::endl;
    os << o.phone_mobile.name() << " = " << o.phone_mobile << std::endl;
    os << o.emails.name() << " = " << o.emails << std::endl;
    os << o.homepage.name() << " = " << o.homepage << std::endl;
    os << o.about.name() << " = " << o.about << std::endl;
    os << o.mood_text.name() << " = " << o.mood_text << std::endl;
    os << o.rich_mood_text.name() << " = " << o.rich_mood_text << std::endl;
    os << o.timezone.name() << " = " << o.timezone << std::endl;
    os << o.profile_timestamp.name() << " = " << o.profile_timestamp << std::endl;
    os << o.nrof_authed_buddies.name() << " = " << o.nrof_authed_buddies << std::endl;
    os << o.ipcountry.name() << " = " << o.ipcountry << std::endl;
    os << o.avatar_timestamp.name() << " = " << o.avatar_timestamp << std::endl;
    os << o.mood_timestamp.name() << " = " << o.mood_timestamp << std::endl;
    os << o.received_authrequest.name() << " = " << o.received_authrequest << std::endl;
    os << o.authreq_timestamp.name() << " = " << o.authreq_timestamp << std::endl;
    os << o.lastonline_timestamp.name() << " = " << o.lastonline_timestamp << std::endl;
    os << o.availability.name() << " = " << o.availability << std::endl;
    os << o.displayname.name() << " = " << o.displayname << std::endl;
    os << o.refreshing.name() << " = " << o.refreshing << std::endl;
    os << o.given_authlevel.name() << " = " << o.given_authlevel << std::endl;
    os << o.given_displayname.name() << " = " << o.given_displayname << std::endl;
    os << o.assigned_speeddial.name() << " = " << o.assigned_speeddial << std::endl;
    os << o.assigned_comment.name() << " = " << o.assigned_comment << std::endl;
    os << o.alertstring.name() << " = " << o.alertstring << std::endl;
    os << o.lastused_timestamp.name() << " = " << o.lastused_timestamp << std::endl;
    os << o.authrequest_count.name() << " = " << o.authrequest_count << std::endl;
    os << o.assigned_phone1.name() << " = " << o.assigned_phone1 << std::endl;
    os << o.assigned_phone1_label.name() << " = " << o.assigned_phone1_label << std::endl;
    os << o.assigned_phone2.name() << " = " << o.assigned_phone2 << std::endl;
    os << o.assigned_phone2_label.name() << " = " << o.assigned_phone2_label << std::endl;
    os << o.assigned_phone3.name() << " = " << o.assigned_phone3 << std::endl;
    os << o.assigned_phone3_label.name() << " = " << o.assigned_phone3_label << std::endl;
    os << o.buddystatus.name() << " = " << o.buddystatus << std::endl;
    os << o.isauthorized.name() << " = " << o.isauthorized << std::endl;
    os << o.popularity_ord.name() << " = " << o.popularity_ord << std::endl;
    os << o.isblocked.name() << " = " << o.isblocked << std::endl;
    os << o.certificate_send_count.name() << " = " << o.certificate_send_count << std::endl;
    os << o.account_modification_serial_nr.name() << " = " << o.account_modification_serial_nr << std::endl;
    os << o.nr_of_buddies.name() << " = " << o.nr_of_buddies << std::endl;
    os << o.server_synced.name() << " = " << o.server_synced << std::endl;
    os << o.contactlist_track.name() << " = " << o.contactlist_track << std::endl;
    os << o.last_used_networktime.name() << " = " << o.last_used_networktime << std::endl;
    os << o.authorized_time.name() << " = " << o.authorized_time << std::endl;
    os << o.sent_authrequest.name() << " = " << o.sent_authrequest << std::endl;
    os << o.sent_authrequest_time.name() << " = " << o.sent_authrequest_time << std::endl;
    os << o.sent_authrequest_serial.name() << " = " << o.sent_authrequest_serial << std::endl;
    os << o.node_capabilities.name() << " = " << o.node_capabilities << std::endl;
    os << o.revoked_auth.name() << " = " << o.revoked_auth << std::endl;
    os << o.added_in_shared_group.name() << " = " << o.added_in_shared_group << std::endl;
    os << o.in_shared_group.name() << " = " << o.in_shared_group << std::endl;
    os << o.stack_version.name() << " = " << o.stack_version << std::endl;
    os << o.offline_authreq_id.name() << " = " << o.offline_authreq_id << std::endl;
    os << o.node_capabilities_and.name() << " = " << o.node_capabilities_and << std::endl;
    os << o.authreq_crc.name() << " = " << o.authreq_crc << std::endl;
    os << o.authreq_src.name() << " = " << o.authreq_src << std::endl;
    os << o.pop_score.name() << " = " << o.pop_score << std::endl;
    os << o.main_phone.name() << " = " << o.main_phone << std::endl;
    os << o.unified_servants.name() << " = " << o.unified_servants << std::endl;
    os << o.phone_home_normalized.name() << " = " << o.phone_home_normalized << std::endl;
    os << o.phone_office_normalized.name() << " = " << o.phone_office_normalized << std::endl;
    os << o.phone_mobile_normalized.name() << " = " << o.phone_mobile_normalized << std::endl;
    os << o.sent_authrequest_initmethod.name() << " = " << o.sent_authrequest_initmethod << std::endl;
    os << o.authreq_initmethod.name() << " = " << o.authreq_initmethod << std::endl;
    os << o.sent_authrequest_extrasbitmask.name() << " = " << o.sent_authrequest_extrasbitmask << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Conversations::Own::Id("id",A_field_type_integer,"Conversations");
const std::string Conversations::type__("Conversations");
const std::string Conversations::table__("Conversations");
const std::string Conversations::sequence__("Conversations_seq");
const litesql::FieldType Conversations::Id("id",A_field_type_integer,table__);
const litesql::FieldType Conversations::Is_permanent("is_permanent",A_field_type_integer,table__);
const litesql::FieldType Conversations::Identity("identity",A_field_type_string,table__);
const litesql::FieldType Conversations::Live_host("live_host",A_field_type_string,table__);
const litesql::FieldType Conversations::Live_start_timestamp("live_start_timestamp",A_field_type_integer,table__);
const litesql::FieldType Conversations::Live_is_muted("live_is_muted",A_field_type_integer,table__);
const litesql::FieldType Conversations::Alert_string("alert_string",A_field_type_string,table__);
const litesql::FieldType Conversations::Is_bookmarked("is_bookmarked",A_field_type_integer,table__);
const litesql::FieldType Conversations::Given_displayname("given_displayname",A_field_type_string,table__);
const litesql::FieldType Conversations::Displayname("displayname",A_field_type_string,table__);
const litesql::FieldType Conversations::Local_livestatus("local_livestatus",A_field_type_integer,table__);
const litesql::FieldType Conversations::Inbox_timestamp("inbox_timestamp",A_field_type_integer,table__);
const litesql::FieldType Conversations::Inbox_message_id("inbox_message_id",A_field_type_integer,table__);
const litesql::FieldType Conversations::Unconsumed_suppressed_messages("unconsumed_suppressed_messages",A_field_type_integer,table__);
const litesql::FieldType Conversations::Unconsumed_normal_messages("unconsumed_normal_messages",A_field_type_integer,table__);
const litesql::FieldType Conversations::Unconsumed_elevated_messages("unconsumed_elevated_messages",A_field_type_integer,table__);
const litesql::FieldType Conversations::Unconsumed_messages_voice("unconsumed_messages_voice",A_field_type_integer,table__);
const litesql::FieldType Conversations::Active_vm_id("active_vm_id",A_field_type_integer,table__);
const litesql::FieldType Conversations::Context_horizon("context_horizon",A_field_type_integer,table__);
const litesql::FieldType Conversations::Consumption_horizon("consumption_horizon",A_field_type_integer,table__);
const litesql::FieldType Conversations::Last_activity_timestamp("last_activity_timestamp",A_field_type_integer,table__);
const litesql::FieldType Conversations::Active_invoice_message("active_invoice_message",A_field_type_integer,table__);
const litesql::FieldType Conversations::Spawned_from_convo_id("spawned_from_convo_id",A_field_type_integer,table__);
const litesql::FieldType Conversations::Pinned_order("pinned_order",A_field_type_integer,table__);
const litesql::FieldType Conversations::Creator("creator",A_field_type_string,table__);
const litesql::FieldType Conversations::Creation_timestamp("creation_timestamp",A_field_type_integer,table__);
const litesql::FieldType Conversations::My_status("my_status",A_field_type_integer,table__);
const litesql::FieldType Conversations::Opt_joining_enabled("opt_joining_enabled",A_field_type_integer,table__);
const litesql::FieldType Conversations::Opt_access_token("opt_access_token",A_field_type_string,table__);
const litesql::FieldType Conversations::Opt_entry_level_rank("opt_entry_level_rank",A_field_type_integer,table__);
const litesql::FieldType Conversations::Opt_disclose_history("opt_disclose_history",A_field_type_integer,table__);
const litesql::FieldType Conversations::Opt_history_limit_in_days("opt_history_limit_in_days",A_field_type_integer,table__);
const litesql::FieldType Conversations::Opt_admin_only_activities("opt_admin_only_activities",A_field_type_integer,table__);
const litesql::FieldType Conversations::Passwordhint("passwordhint",A_field_type_string,table__);
const litesql::FieldType Conversations::Meta_name("meta_name",A_field_type_string,table__);
const litesql::FieldType Conversations::Meta_topic("meta_topic",A_field_type_string,table__);
const litesql::FieldType Conversations::Meta_guidelines("meta_guidelines",A_field_type_string,table__);
const litesql::FieldType Conversations::Meta_picture("meta_picture",A_field_type_blob,table__);
const litesql::FieldType Conversations::Premium_video_status("premium_video_status",A_field_type_integer,table__);
const litesql::FieldType Conversations::Premium_video_is_grace_period("premium_video_is_grace_period",A_field_type_integer,table__);
const litesql::FieldType Conversations::Guid("guid",A_field_type_string,table__);
const litesql::FieldType Conversations::Dialog_partner("dialog_partner",A_field_type_string,table__);
const litesql::FieldType Conversations::Meta_description("meta_description",A_field_type_string,table__);
const litesql::FieldType Conversations::Premium_video_sponsor_list("premium_video_sponsor_list",A_field_type_string,table__);
const litesql::FieldType Conversations::Mcr_caller("mcr_caller",A_field_type_string,table__);
const litesql::FieldType Conversations::Chat_dbid("chat_dbid",A_field_type_integer,table__);
const litesql::FieldType Conversations::History_horizon("history_horizon",A_field_type_integer,table__);
const litesql::FieldType Conversations::History_sync_state("history_sync_state",A_field_type_string,table__);
const litesql::FieldType Conversations::Is_blocked("is_blocked",A_field_type_integer,table__);
const litesql::FieldType Conversations::Last_message_id("last_message_id",A_field_type_integer,table__);
const litesql::FieldType Conversations::Picture("picture",A_field_type_string,table__);
const litesql::FieldType Conversations::Is_p2p_migrated("is_p2p_migrated",A_field_type_integer,table__);
const litesql::FieldType Conversations::Thread_version("thread_version",A_field_type_string,table__);
const litesql::FieldType Conversations::Consumption_horizon_set_at("consumption_horizon_set_at",A_field_type_integer,table__);
const litesql::FieldType Conversations::Alt_identity("alt_identity",A_field_type_string,table__);
const litesql::FieldType Conversations::In_migrated_thread_since("in_migrated_thread_since",A_field_type_integer,table__);
void Conversations::initValues() {
}
void Conversations::defaults() {
    id = 0;
    is_permanent = 0;
    live_start_timestamp = 0;
    live_is_muted = 0;
    is_bookmarked = 0;
    local_livestatus = 0;
    inbox_timestamp = 0;
    inbox_message_id = 0;
    unconsumed_suppressed_messages = 0;
    unconsumed_normal_messages = 0;
    unconsumed_elevated_messages = 0;
    unconsumed_messages_voice = 0;
    active_vm_id = 0;
    context_horizon = 0;
    consumption_horizon = 0;
    last_activity_timestamp = 0;
    active_invoice_message = 0;
    spawned_from_convo_id = 0;
    pinned_order = 0;
    creation_timestamp = 0;
    my_status = 0;
    opt_joining_enabled = 0;
    opt_entry_level_rank = 0;
    opt_disclose_history = 0;
    opt_history_limit_in_days = 0;
    opt_admin_only_activities = 0;
    meta_picture = Blob();
    premium_video_status = 0;
    premium_video_is_grace_period = 0;
    chat_dbid = 0;
    history_horizon = 0;
    is_blocked = 0;
    last_message_id = 0;
    is_p2p_migrated = 0;
    consumption_horizon_set_at = 0;
    in_migrated_thread_since = 0;
}
Conversations::Conversations(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), is_permanent(Is_permanent), identity(Identity), live_host(Live_host), live_start_timestamp(Live_start_timestamp), live_is_muted(Live_is_muted), alert_string(Alert_string), is_bookmarked(Is_bookmarked), given_displayname(Given_displayname), displayname(Displayname), local_livestatus(Local_livestatus), inbox_timestamp(Inbox_timestamp), inbox_message_id(Inbox_message_id), unconsumed_suppressed_messages(Unconsumed_suppressed_messages), unconsumed_normal_messages(Unconsumed_normal_messages), unconsumed_elevated_messages(Unconsumed_elevated_messages), unconsumed_messages_voice(Unconsumed_messages_voice), active_vm_id(Active_vm_id), context_horizon(Context_horizon), consumption_horizon(Consumption_horizon), last_activity_timestamp(Last_activity_timestamp), active_invoice_message(Active_invoice_message), spawned_from_convo_id(Spawned_from_convo_id), pinned_order(Pinned_order), creator(Creator), creation_timestamp(Creation_timestamp), my_status(My_status), opt_joining_enabled(Opt_joining_enabled), opt_access_token(Opt_access_token), opt_entry_level_rank(Opt_entry_level_rank), opt_disclose_history(Opt_disclose_history), opt_history_limit_in_days(Opt_history_limit_in_days), opt_admin_only_activities(Opt_admin_only_activities), passwordhint(Passwordhint), meta_name(Meta_name), meta_topic(Meta_topic), meta_guidelines(Meta_guidelines), meta_picture(Meta_picture), premium_video_status(Premium_video_status), premium_video_is_grace_period(Premium_video_is_grace_period), guid(Guid), dialog_partner(Dialog_partner), meta_description(Meta_description), premium_video_sponsor_list(Premium_video_sponsor_list), mcr_caller(Mcr_caller), chat_dbid(Chat_dbid), history_horizon(History_horizon), history_sync_state(History_sync_state), is_blocked(Is_blocked), last_message_id(Last_message_id), picture(Picture), is_p2p_migrated(Is_p2p_migrated), thread_version(Thread_version), consumption_horizon_set_at(Consumption_horizon_set_at), alt_identity(Alt_identity), in_migrated_thread_since(In_migrated_thread_since) {
    defaults();
}
Conversations::Conversations(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), is_permanent(Is_permanent), identity(Identity), live_host(Live_host), live_start_timestamp(Live_start_timestamp), live_is_muted(Live_is_muted), alert_string(Alert_string), is_bookmarked(Is_bookmarked), given_displayname(Given_displayname), displayname(Displayname), local_livestatus(Local_livestatus), inbox_timestamp(Inbox_timestamp), inbox_message_id(Inbox_message_id), unconsumed_suppressed_messages(Unconsumed_suppressed_messages), unconsumed_normal_messages(Unconsumed_normal_messages), unconsumed_elevated_messages(Unconsumed_elevated_messages), unconsumed_messages_voice(Unconsumed_messages_voice), active_vm_id(Active_vm_id), context_horizon(Context_horizon), consumption_horizon(Consumption_horizon), last_activity_timestamp(Last_activity_timestamp), active_invoice_message(Active_invoice_message), spawned_from_convo_id(Spawned_from_convo_id), pinned_order(Pinned_order), creator(Creator), creation_timestamp(Creation_timestamp), my_status(My_status), opt_joining_enabled(Opt_joining_enabled), opt_access_token(Opt_access_token), opt_entry_level_rank(Opt_entry_level_rank), opt_disclose_history(Opt_disclose_history), opt_history_limit_in_days(Opt_history_limit_in_days), opt_admin_only_activities(Opt_admin_only_activities), passwordhint(Passwordhint), meta_name(Meta_name), meta_topic(Meta_topic), meta_guidelines(Meta_guidelines), meta_picture(Meta_picture), premium_video_status(Premium_video_status), premium_video_is_grace_period(Premium_video_is_grace_period), guid(Guid), dialog_partner(Dialog_partner), meta_description(Meta_description), premium_video_sponsor_list(Premium_video_sponsor_list), mcr_caller(Mcr_caller), chat_dbid(Chat_dbid), history_horizon(History_horizon), history_sync_state(History_sync_state), is_blocked(Is_blocked), last_message_id(Last_message_id), picture(Picture), is_p2p_migrated(Is_p2p_migrated), thread_version(Thread_version), consumption_horizon_set_at(Consumption_horizon_set_at), alt_identity(Alt_identity), in_migrated_thread_since(In_migrated_thread_since) {
    defaults();
    size_t size = (rec.size() > 56) ? 56 : rec.size();
    switch(size) {
    case 56: in_migrated_thread_since = convert<const std::string&, int>(rec[55]);
        in_migrated_thread_since.setModified(false);
    case 55: alt_identity = convert<const std::string&, std::string>(rec[54]);
        alt_identity.setModified(false);
    case 54: consumption_horizon_set_at = convert<const std::string&, int>(rec[53]);
        consumption_horizon_set_at.setModified(false);
    case 53: thread_version = convert<const std::string&, std::string>(rec[52]);
        thread_version.setModified(false);
    case 52: is_p2p_migrated = convert<const std::string&, int>(rec[51]);
        is_p2p_migrated.setModified(false);
    case 51: picture = convert<const std::string&, std::string>(rec[50]);
        picture.setModified(false);
    case 50: last_message_id = convert<const std::string&, int>(rec[49]);
        last_message_id.setModified(false);
    case 49: is_blocked = convert<const std::string&, int>(rec[48]);
        is_blocked.setModified(false);
    case 48: history_sync_state = convert<const std::string&, std::string>(rec[47]);
        history_sync_state.setModified(false);
    case 47: history_horizon = convert<const std::string&, int>(rec[46]);
        history_horizon.setModified(false);
    case 46: chat_dbid = convert<const std::string&, int>(rec[45]);
        chat_dbid.setModified(false);
    case 45: mcr_caller = convert<const std::string&, std::string>(rec[44]);
        mcr_caller.setModified(false);
    case 44: premium_video_sponsor_list = convert<const std::string&, std::string>(rec[43]);
        premium_video_sponsor_list.setModified(false);
    case 43: meta_description = convert<const std::string&, std::string>(rec[42]);
        meta_description.setModified(false);
    case 42: dialog_partner = convert<const std::string&, std::string>(rec[41]);
        dialog_partner.setModified(false);
    case 41: guid = convert<const std::string&, std::string>(rec[40]);
        guid.setModified(false);
    case 40: premium_video_is_grace_period = convert<const std::string&, int>(rec[39]);
        premium_video_is_grace_period.setModified(false);
    case 39: premium_video_status = convert<const std::string&, int>(rec[38]);
        premium_video_status.setModified(false);
    case 38: meta_picture = convert<const std::string&, litesql::Blob>(rec[37]);
        meta_picture.setModified(false);
    case 37: meta_guidelines = convert<const std::string&, std::string>(rec[36]);
        meta_guidelines.setModified(false);
    case 36: meta_topic = convert<const std::string&, std::string>(rec[35]);
        meta_topic.setModified(false);
    case 35: meta_name = convert<const std::string&, std::string>(rec[34]);
        meta_name.setModified(false);
    case 34: passwordhint = convert<const std::string&, std::string>(rec[33]);
        passwordhint.setModified(false);
    case 33: opt_admin_only_activities = convert<const std::string&, int>(rec[32]);
        opt_admin_only_activities.setModified(false);
    case 32: opt_history_limit_in_days = convert<const std::string&, int>(rec[31]);
        opt_history_limit_in_days.setModified(false);
    case 31: opt_disclose_history = convert<const std::string&, int>(rec[30]);
        opt_disclose_history.setModified(false);
    case 30: opt_entry_level_rank = convert<const std::string&, int>(rec[29]);
        opt_entry_level_rank.setModified(false);
    case 29: opt_access_token = convert<const std::string&, std::string>(rec[28]);
        opt_access_token.setModified(false);
    case 28: opt_joining_enabled = convert<const std::string&, int>(rec[27]);
        opt_joining_enabled.setModified(false);
    case 27: my_status = convert<const std::string&, int>(rec[26]);
        my_status.setModified(false);
    case 26: creation_timestamp = convert<const std::string&, int>(rec[25]);
        creation_timestamp.setModified(false);
    case 25: creator = convert<const std::string&, std::string>(rec[24]);
        creator.setModified(false);
    case 24: pinned_order = convert<const std::string&, int>(rec[23]);
        pinned_order.setModified(false);
    case 23: spawned_from_convo_id = convert<const std::string&, int>(rec[22]);
        spawned_from_convo_id.setModified(false);
    case 22: active_invoice_message = convert<const std::string&, int>(rec[21]);
        active_invoice_message.setModified(false);
    case 21: last_activity_timestamp = convert<const std::string&, int>(rec[20]);
        last_activity_timestamp.setModified(false);
    case 20: consumption_horizon = convert<const std::string&, int>(rec[19]);
        consumption_horizon.setModified(false);
    case 19: context_horizon = convert<const std::string&, int>(rec[18]);
        context_horizon.setModified(false);
    case 18: active_vm_id = convert<const std::string&, int>(rec[17]);
        active_vm_id.setModified(false);
    case 17: unconsumed_messages_voice = convert<const std::string&, int>(rec[16]);
        unconsumed_messages_voice.setModified(false);
    case 16: unconsumed_elevated_messages = convert<const std::string&, int>(rec[15]);
        unconsumed_elevated_messages.setModified(false);
    case 15: unconsumed_normal_messages = convert<const std::string&, int>(rec[14]);
        unconsumed_normal_messages.setModified(false);
    case 14: unconsumed_suppressed_messages = convert<const std::string&, int>(rec[13]);
        unconsumed_suppressed_messages.setModified(false);
    case 13: inbox_message_id = convert<const std::string&, int>(rec[12]);
        inbox_message_id.setModified(false);
    case 12: inbox_timestamp = convert<const std::string&, int>(rec[11]);
        inbox_timestamp.setModified(false);
    case 11: local_livestatus = convert<const std::string&, int>(rec[10]);
        local_livestatus.setModified(false);
    case 10: displayname = convert<const std::string&, std::string>(rec[9]);
        displayname.setModified(false);
    case 9: given_displayname = convert<const std::string&, std::string>(rec[8]);
        given_displayname.setModified(false);
    case 8: is_bookmarked = convert<const std::string&, int>(rec[7]);
        is_bookmarked.setModified(false);
    case 7: alert_string = convert<const std::string&, std::string>(rec[6]);
        alert_string.setModified(false);
    case 6: live_is_muted = convert<const std::string&, int>(rec[5]);
        live_is_muted.setModified(false);
    case 5: live_start_timestamp = convert<const std::string&, int>(rec[4]);
        live_start_timestamp.setModified(false);
    case 4: live_host = convert<const std::string&, std::string>(rec[3]);
        live_host.setModified(false);
    case 3: identity = convert<const std::string&, std::string>(rec[2]);
        identity.setModified(false);
    case 2: is_permanent = convert<const std::string&, int>(rec[1]);
        is_permanent.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Conversations::Conversations(const Conversations& obj)
     : litesql::Persistent(obj), id(obj.id), is_permanent(obj.is_permanent), identity(obj.identity), live_host(obj.live_host), live_start_timestamp(obj.live_start_timestamp), live_is_muted(obj.live_is_muted), alert_string(obj.alert_string), is_bookmarked(obj.is_bookmarked), given_displayname(obj.given_displayname), displayname(obj.displayname), local_livestatus(obj.local_livestatus), inbox_timestamp(obj.inbox_timestamp), inbox_message_id(obj.inbox_message_id), unconsumed_suppressed_messages(obj.unconsumed_suppressed_messages), unconsumed_normal_messages(obj.unconsumed_normal_messages), unconsumed_elevated_messages(obj.unconsumed_elevated_messages), unconsumed_messages_voice(obj.unconsumed_messages_voice), active_vm_id(obj.active_vm_id), context_horizon(obj.context_horizon), consumption_horizon(obj.consumption_horizon), last_activity_timestamp(obj.last_activity_timestamp), active_invoice_message(obj.active_invoice_message), spawned_from_convo_id(obj.spawned_from_convo_id), pinned_order(obj.pinned_order), creator(obj.creator), creation_timestamp(obj.creation_timestamp), my_status(obj.my_status), opt_joining_enabled(obj.opt_joining_enabled), opt_access_token(obj.opt_access_token), opt_entry_level_rank(obj.opt_entry_level_rank), opt_disclose_history(obj.opt_disclose_history), opt_history_limit_in_days(obj.opt_history_limit_in_days), opt_admin_only_activities(obj.opt_admin_only_activities), passwordhint(obj.passwordhint), meta_name(obj.meta_name), meta_topic(obj.meta_topic), meta_guidelines(obj.meta_guidelines), meta_picture(obj.meta_picture), premium_video_status(obj.premium_video_status), premium_video_is_grace_period(obj.premium_video_is_grace_period), guid(obj.guid), dialog_partner(obj.dialog_partner), meta_description(obj.meta_description), premium_video_sponsor_list(obj.premium_video_sponsor_list), mcr_caller(obj.mcr_caller), chat_dbid(obj.chat_dbid), history_horizon(obj.history_horizon), history_sync_state(obj.history_sync_state), is_blocked(obj.is_blocked), last_message_id(obj.last_message_id), picture(obj.picture), is_p2p_migrated(obj.is_p2p_migrated), thread_version(obj.thread_version), consumption_horizon_set_at(obj.consumption_horizon_set_at), alt_identity(obj.alt_identity), in_migrated_thread_since(obj.in_migrated_thread_since) {
}
const Conversations& Conversations::operator=(const Conversations& obj) {
    if (this != &obj) {
        id = obj.id;
        is_permanent = obj.is_permanent;
        identity = obj.identity;
        live_host = obj.live_host;
        live_start_timestamp = obj.live_start_timestamp;
        live_is_muted = obj.live_is_muted;
        alert_string = obj.alert_string;
        is_bookmarked = obj.is_bookmarked;
        given_displayname = obj.given_displayname;
        displayname = obj.displayname;
        local_livestatus = obj.local_livestatus;
        inbox_timestamp = obj.inbox_timestamp;
        inbox_message_id = obj.inbox_message_id;
        unconsumed_suppressed_messages = obj.unconsumed_suppressed_messages;
        unconsumed_normal_messages = obj.unconsumed_normal_messages;
        unconsumed_elevated_messages = obj.unconsumed_elevated_messages;
        unconsumed_messages_voice = obj.unconsumed_messages_voice;
        active_vm_id = obj.active_vm_id;
        context_horizon = obj.context_horizon;
        consumption_horizon = obj.consumption_horizon;
        last_activity_timestamp = obj.last_activity_timestamp;
        active_invoice_message = obj.active_invoice_message;
        spawned_from_convo_id = obj.spawned_from_convo_id;
        pinned_order = obj.pinned_order;
        creator = obj.creator;
        creation_timestamp = obj.creation_timestamp;
        my_status = obj.my_status;
        opt_joining_enabled = obj.opt_joining_enabled;
        opt_access_token = obj.opt_access_token;
        opt_entry_level_rank = obj.opt_entry_level_rank;
        opt_disclose_history = obj.opt_disclose_history;
        opt_history_limit_in_days = obj.opt_history_limit_in_days;
        opt_admin_only_activities = obj.opt_admin_only_activities;
        passwordhint = obj.passwordhint;
        meta_name = obj.meta_name;
        meta_topic = obj.meta_topic;
        meta_guidelines = obj.meta_guidelines;
        meta_picture = obj.meta_picture;
        premium_video_status = obj.premium_video_status;
        premium_video_is_grace_period = obj.premium_video_is_grace_period;
        guid = obj.guid;
        dialog_partner = obj.dialog_partner;
        meta_description = obj.meta_description;
        premium_video_sponsor_list = obj.premium_video_sponsor_list;
        mcr_caller = obj.mcr_caller;
        chat_dbid = obj.chat_dbid;
        history_horizon = obj.history_horizon;
        history_sync_state = obj.history_sync_state;
        is_blocked = obj.is_blocked;
        last_message_id = obj.last_message_id;
        picture = obj.picture;
        is_p2p_migrated = obj.is_p2p_migrated;
        thread_version = obj.thread_version;
        consumption_horizon_set_at = obj.consumption_horizon_set_at;
        alt_identity = obj.alt_identity;
        in_migrated_thread_since = obj.in_migrated_thread_since;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string Conversations::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(is_permanent.name());
    values.push_back(is_permanent);
    is_permanent.setModified(false);
    fields.push_back(identity.name());
    values.push_back(identity);
    identity.setModified(false);
    fields.push_back(live_host.name());
    values.push_back(live_host);
    live_host.setModified(false);
    fields.push_back(live_start_timestamp.name());
    values.push_back(live_start_timestamp);
    live_start_timestamp.setModified(false);
    fields.push_back(live_is_muted.name());
    values.push_back(live_is_muted);
    live_is_muted.setModified(false);
    fields.push_back(alert_string.name());
    values.push_back(alert_string);
    alert_string.setModified(false);
    fields.push_back(is_bookmarked.name());
    values.push_back(is_bookmarked);
    is_bookmarked.setModified(false);
    fields.push_back(given_displayname.name());
    values.push_back(given_displayname);
    given_displayname.setModified(false);
    fields.push_back(displayname.name());
    values.push_back(displayname);
    displayname.setModified(false);
    fields.push_back(local_livestatus.name());
    values.push_back(local_livestatus);
    local_livestatus.setModified(false);
    fields.push_back(inbox_timestamp.name());
    values.push_back(inbox_timestamp);
    inbox_timestamp.setModified(false);
    fields.push_back(inbox_message_id.name());
    values.push_back(inbox_message_id);
    inbox_message_id.setModified(false);
    fields.push_back(unconsumed_suppressed_messages.name());
    values.push_back(unconsumed_suppressed_messages);
    unconsumed_suppressed_messages.setModified(false);
    fields.push_back(unconsumed_normal_messages.name());
    values.push_back(unconsumed_normal_messages);
    unconsumed_normal_messages.setModified(false);
    fields.push_back(unconsumed_elevated_messages.name());
    values.push_back(unconsumed_elevated_messages);
    unconsumed_elevated_messages.setModified(false);
    fields.push_back(unconsumed_messages_voice.name());
    values.push_back(unconsumed_messages_voice);
    unconsumed_messages_voice.setModified(false);
    fields.push_back(active_vm_id.name());
    values.push_back(active_vm_id);
    active_vm_id.setModified(false);
    fields.push_back(context_horizon.name());
    values.push_back(context_horizon);
    context_horizon.setModified(false);
    fields.push_back(consumption_horizon.name());
    values.push_back(consumption_horizon);
    consumption_horizon.setModified(false);
    fields.push_back(last_activity_timestamp.name());
    values.push_back(last_activity_timestamp);
    last_activity_timestamp.setModified(false);
    fields.push_back(active_invoice_message.name());
    values.push_back(active_invoice_message);
    active_invoice_message.setModified(false);
    fields.push_back(spawned_from_convo_id.name());
    values.push_back(spawned_from_convo_id);
    spawned_from_convo_id.setModified(false);
    fields.push_back(pinned_order.name());
    values.push_back(pinned_order);
    pinned_order.setModified(false);
    fields.push_back(creator.name());
    values.push_back(creator);
    creator.setModified(false);
    fields.push_back(creation_timestamp.name());
    values.push_back(creation_timestamp);
    creation_timestamp.setModified(false);
    fields.push_back(my_status.name());
    values.push_back(my_status);
    my_status.setModified(false);
    fields.push_back(opt_joining_enabled.name());
    values.push_back(opt_joining_enabled);
    opt_joining_enabled.setModified(false);
    fields.push_back(opt_access_token.name());
    values.push_back(opt_access_token);
    opt_access_token.setModified(false);
    fields.push_back(opt_entry_level_rank.name());
    values.push_back(opt_entry_level_rank);
    opt_entry_level_rank.setModified(false);
    fields.push_back(opt_disclose_history.name());
    values.push_back(opt_disclose_history);
    opt_disclose_history.setModified(false);
    fields.push_back(opt_history_limit_in_days.name());
    values.push_back(opt_history_limit_in_days);
    opt_history_limit_in_days.setModified(false);
    fields.push_back(opt_admin_only_activities.name());
    values.push_back(opt_admin_only_activities);
    opt_admin_only_activities.setModified(false);
    fields.push_back(passwordhint.name());
    values.push_back(passwordhint);
    passwordhint.setModified(false);
    fields.push_back(meta_name.name());
    values.push_back(meta_name);
    meta_name.setModified(false);
    fields.push_back(meta_topic.name());
    values.push_back(meta_topic);
    meta_topic.setModified(false);
    fields.push_back(meta_guidelines.name());
    values.push_back(meta_guidelines);
    meta_guidelines.setModified(false);
    fields.push_back(meta_picture.name());
    values.push_back(meta_picture);
    meta_picture.setModified(false);
    fields.push_back(premium_video_status.name());
    values.push_back(premium_video_status);
    premium_video_status.setModified(false);
    fields.push_back(premium_video_is_grace_period.name());
    values.push_back(premium_video_is_grace_period);
    premium_video_is_grace_period.setModified(false);
    fields.push_back(guid.name());
    values.push_back(guid);
    guid.setModified(false);
    fields.push_back(dialog_partner.name());
    values.push_back(dialog_partner);
    dialog_partner.setModified(false);
    fields.push_back(meta_description.name());
    values.push_back(meta_description);
    meta_description.setModified(false);
    fields.push_back(premium_video_sponsor_list.name());
    values.push_back(premium_video_sponsor_list);
    premium_video_sponsor_list.setModified(false);
    fields.push_back(mcr_caller.name());
    values.push_back(mcr_caller);
    mcr_caller.setModified(false);
    fields.push_back(chat_dbid.name());
    values.push_back(chat_dbid);
    chat_dbid.setModified(false);
    fields.push_back(history_horizon.name());
    values.push_back(history_horizon);
    history_horizon.setModified(false);
    fields.push_back(history_sync_state.name());
    values.push_back(history_sync_state);
    history_sync_state.setModified(false);
    fields.push_back(is_blocked.name());
    values.push_back(is_blocked);
    is_blocked.setModified(false);
    fields.push_back(last_message_id.name());
    values.push_back(last_message_id);
    last_message_id.setModified(false);
    fields.push_back(picture.name());
    values.push_back(picture);
    picture.setModified(false);
    fields.push_back(is_p2p_migrated.name());
    values.push_back(is_p2p_migrated);
    is_p2p_migrated.setModified(false);
    fields.push_back(thread_version.name());
    values.push_back(thread_version);
    thread_version.setModified(false);
    fields.push_back(consumption_horizon_set_at.name());
    values.push_back(consumption_horizon_set_at);
    consumption_horizon_set_at.setModified(false);
    fields.push_back(alt_identity.name());
    values.push_back(alt_identity);
    alt_identity.setModified(false);
    fields.push_back(in_migrated_thread_since.name());
    values.push_back(in_migrated_thread_since);
    in_migrated_thread_since.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Conversations::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    //Type processing disabled
    //type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Conversations::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, is_permanent);
    updateField(updates, table__, identity);
    updateField(updates, table__, live_host);
    updateField(updates, table__, live_start_timestamp);
    updateField(updates, table__, live_is_muted);
    updateField(updates, table__, alert_string);
    updateField(updates, table__, is_bookmarked);
    updateField(updates, table__, given_displayname);
    updateField(updates, table__, displayname);
    updateField(updates, table__, local_livestatus);
    updateField(updates, table__, inbox_timestamp);
    updateField(updates, table__, inbox_message_id);
    updateField(updates, table__, unconsumed_suppressed_messages);
    updateField(updates, table__, unconsumed_normal_messages);
    updateField(updates, table__, unconsumed_elevated_messages);
    updateField(updates, table__, unconsumed_messages_voice);
    updateField(updates, table__, active_vm_id);
    updateField(updates, table__, context_horizon);
    updateField(updates, table__, consumption_horizon);
    updateField(updates, table__, last_activity_timestamp);
    updateField(updates, table__, active_invoice_message);
    updateField(updates, table__, spawned_from_convo_id);
    updateField(updates, table__, pinned_order);
    updateField(updates, table__, creator);
    updateField(updates, table__, creation_timestamp);
    updateField(updates, table__, my_status);
    updateField(updates, table__, opt_joining_enabled);
    updateField(updates, table__, opt_access_token);
    updateField(updates, table__, opt_entry_level_rank);
    updateField(updates, table__, opt_disclose_history);
    updateField(updates, table__, opt_history_limit_in_days);
    updateField(updates, table__, opt_admin_only_activities);
    updateField(updates, table__, passwordhint);
    updateField(updates, table__, meta_name);
    updateField(updates, table__, meta_topic);
    updateField(updates, table__, meta_guidelines);
    updateField(updates, table__, meta_picture);
    updateField(updates, table__, premium_video_status);
    updateField(updates, table__, premium_video_is_grace_period);
    updateField(updates, table__, guid);
    updateField(updates, table__, dialog_partner);
    updateField(updates, table__, meta_description);
    updateField(updates, table__, premium_video_sponsor_list);
    updateField(updates, table__, mcr_caller);
    updateField(updates, table__, chat_dbid);
    updateField(updates, table__, history_horizon);
    updateField(updates, table__, history_sync_state);
    updateField(updates, table__, is_blocked);
    updateField(updates, table__, last_message_id);
    updateField(updates, table__, picture);
    updateField(updates, table__, is_p2p_migrated);
    updateField(updates, table__, thread_version);
    updateField(updates, table__, consumption_horizon_set_at);
    updateField(updates, table__, alt_identity);
    updateField(updates, table__, in_migrated_thread_since);
}
void Conversations::addIDUpdates(Updates& updates) {
}
void Conversations::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Is_permanent);
    ftypes.push_back(Identity);
    ftypes.push_back(Live_host);
    ftypes.push_back(Live_start_timestamp);
    ftypes.push_back(Live_is_muted);
    ftypes.push_back(Alert_string);
    ftypes.push_back(Is_bookmarked);
    ftypes.push_back(Given_displayname);
    ftypes.push_back(Displayname);
    ftypes.push_back(Local_livestatus);
    ftypes.push_back(Inbox_timestamp);
    ftypes.push_back(Inbox_message_id);
    ftypes.push_back(Unconsumed_suppressed_messages);
    ftypes.push_back(Unconsumed_normal_messages);
    ftypes.push_back(Unconsumed_elevated_messages);
    ftypes.push_back(Unconsumed_messages_voice);
    ftypes.push_back(Active_vm_id);
    ftypes.push_back(Context_horizon);
    ftypes.push_back(Consumption_horizon);
    ftypes.push_back(Last_activity_timestamp);
    ftypes.push_back(Active_invoice_message);
    ftypes.push_back(Spawned_from_convo_id);
    ftypes.push_back(Pinned_order);
    ftypes.push_back(Creator);
    ftypes.push_back(Creation_timestamp);
    ftypes.push_back(My_status);
    ftypes.push_back(Opt_joining_enabled);
    ftypes.push_back(Opt_access_token);
    ftypes.push_back(Opt_entry_level_rank);
    ftypes.push_back(Opt_disclose_history);
    ftypes.push_back(Opt_history_limit_in_days);
    ftypes.push_back(Opt_admin_only_activities);
    ftypes.push_back(Passwordhint);
    ftypes.push_back(Meta_name);
    ftypes.push_back(Meta_topic);
    ftypes.push_back(Meta_guidelines);
    ftypes.push_back(Meta_picture);
    ftypes.push_back(Premium_video_status);
    ftypes.push_back(Premium_video_is_grace_period);
    ftypes.push_back(Guid);
    ftypes.push_back(Dialog_partner);
    ftypes.push_back(Meta_description);
    ftypes.push_back(Premium_video_sponsor_list);
    ftypes.push_back(Mcr_caller);
    ftypes.push_back(Chat_dbid);
    ftypes.push_back(History_horizon);
    ftypes.push_back(History_sync_state);
    ftypes.push_back(Is_blocked);
    ftypes.push_back(Last_message_id);
    ftypes.push_back(Picture);
    ftypes.push_back(Is_p2p_migrated);
    ftypes.push_back(Thread_version);
    ftypes.push_back(Consumption_horizon_set_at);
    ftypes.push_back(Alt_identity);
    ftypes.push_back(In_migrated_thread_since);
}
void Conversations::delRecord() {
    deleteFromTable(table__, id);
}
void Conversations::delRelations() {
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
    return true;
}
std::unique_ptr<Conversations> Conversations::upcast() const {
    return unique_ptr<Conversations>(new Conversations(*this));
}
std::unique_ptr<Conversations> Conversations::upcastCopy() const {
    Conversations* np = new Conversations(*this);
    np->id = id;
    np->is_permanent = is_permanent;
    np->identity = identity;
    np->live_host = live_host;
    np->live_start_timestamp = live_start_timestamp;
    np->live_is_muted = live_is_muted;
    np->alert_string = alert_string;
    np->is_bookmarked = is_bookmarked;
    np->given_displayname = given_displayname;
    np->displayname = displayname;
    np->local_livestatus = local_livestatus;
    np->inbox_timestamp = inbox_timestamp;
    np->inbox_message_id = inbox_message_id;
    np->unconsumed_suppressed_messages = unconsumed_suppressed_messages;
    np->unconsumed_normal_messages = unconsumed_normal_messages;
    np->unconsumed_elevated_messages = unconsumed_elevated_messages;
    np->unconsumed_messages_voice = unconsumed_messages_voice;
    np->active_vm_id = active_vm_id;
    np->context_horizon = context_horizon;
    np->consumption_horizon = consumption_horizon;
    np->last_activity_timestamp = last_activity_timestamp;
    np->active_invoice_message = active_invoice_message;
    np->spawned_from_convo_id = spawned_from_convo_id;
    np->pinned_order = pinned_order;
    np->creator = creator;
    np->creation_timestamp = creation_timestamp;
    np->my_status = my_status;
    np->opt_joining_enabled = opt_joining_enabled;
    np->opt_access_token = opt_access_token;
    np->opt_entry_level_rank = opt_entry_level_rank;
    np->opt_disclose_history = opt_disclose_history;
    np->opt_history_limit_in_days = opt_history_limit_in_days;
    np->opt_admin_only_activities = opt_admin_only_activities;
    np->passwordhint = passwordhint;
    np->meta_name = meta_name;
    np->meta_topic = meta_topic;
    np->meta_guidelines = meta_guidelines;
    np->meta_picture = meta_picture;
    np->premium_video_status = premium_video_status;
    np->premium_video_is_grace_period = premium_video_is_grace_period;
    np->guid = guid;
    np->dialog_partner = dialog_partner;
    np->meta_description = meta_description;
    np->premium_video_sponsor_list = premium_video_sponsor_list;
    np->mcr_caller = mcr_caller;
    np->chat_dbid = chat_dbid;
    np->history_horizon = history_horizon;
    np->history_sync_state = history_sync_state;
    np->is_blocked = is_blocked;
    np->last_message_id = last_message_id;
    np->picture = picture;
    np->is_p2p_migrated = is_p2p_migrated;
    np->thread_version = thread_version;
    np->consumption_horizon_set_at = consumption_horizon_set_at;
    np->alt_identity = alt_identity;
    np->in_migrated_thread_since = in_migrated_thread_since;
    np->inDatabase = inDatabase;
    return unique_ptr<Conversations>(np);
}
std::ostream & operator<<(std::ostream& os, Conversations o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.is_permanent.name() << " = " << o.is_permanent << std::endl;
    os << o.identity.name() << " = " << o.identity << std::endl;
    os << o.live_host.name() << " = " << o.live_host << std::endl;
    os << o.live_start_timestamp.name() << " = " << o.live_start_timestamp << std::endl;
    os << o.live_is_muted.name() << " = " << o.live_is_muted << std::endl;
    os << o.alert_string.name() << " = " << o.alert_string << std::endl;
    os << o.is_bookmarked.name() << " = " << o.is_bookmarked << std::endl;
    os << o.given_displayname.name() << " = " << o.given_displayname << std::endl;
    os << o.displayname.name() << " = " << o.displayname << std::endl;
    os << o.local_livestatus.name() << " = " << o.local_livestatus << std::endl;
    os << o.inbox_timestamp.name() << " = " << o.inbox_timestamp << std::endl;
    os << o.inbox_message_id.name() << " = " << o.inbox_message_id << std::endl;
    os << o.unconsumed_suppressed_messages.name() << " = " << o.unconsumed_suppressed_messages << std::endl;
    os << o.unconsumed_normal_messages.name() << " = " << o.unconsumed_normal_messages << std::endl;
    os << o.unconsumed_elevated_messages.name() << " = " << o.unconsumed_elevated_messages << std::endl;
    os << o.unconsumed_messages_voice.name() << " = " << o.unconsumed_messages_voice << std::endl;
    os << o.active_vm_id.name() << " = " << o.active_vm_id << std::endl;
    os << o.context_horizon.name() << " = " << o.context_horizon << std::endl;
    os << o.consumption_horizon.name() << " = " << o.consumption_horizon << std::endl;
    os << o.last_activity_timestamp.name() << " = " << o.last_activity_timestamp << std::endl;
    os << o.active_invoice_message.name() << " = " << o.active_invoice_message << std::endl;
    os << o.spawned_from_convo_id.name() << " = " << o.spawned_from_convo_id << std::endl;
    os << o.pinned_order.name() << " = " << o.pinned_order << std::endl;
    os << o.creator.name() << " = " << o.creator << std::endl;
    os << o.creation_timestamp.name() << " = " << o.creation_timestamp << std::endl;
    os << o.my_status.name() << " = " << o.my_status << std::endl;
    os << o.opt_joining_enabled.name() << " = " << o.opt_joining_enabled << std::endl;
    os << o.opt_access_token.name() << " = " << o.opt_access_token << std::endl;
    os << o.opt_entry_level_rank.name() << " = " << o.opt_entry_level_rank << std::endl;
    os << o.opt_disclose_history.name() << " = " << o.opt_disclose_history << std::endl;
    os << o.opt_history_limit_in_days.name() << " = " << o.opt_history_limit_in_days << std::endl;
    os << o.opt_admin_only_activities.name() << " = " << o.opt_admin_only_activities << std::endl;
    os << o.passwordhint.name() << " = " << o.passwordhint << std::endl;
    os << o.meta_name.name() << " = " << o.meta_name << std::endl;
    os << o.meta_topic.name() << " = " << o.meta_topic << std::endl;
    os << o.meta_guidelines.name() << " = " << o.meta_guidelines << std::endl;
    os << o.meta_picture.name() << " = " << o.meta_picture << std::endl;
    os << o.premium_video_status.name() << " = " << o.premium_video_status << std::endl;
    os << o.premium_video_is_grace_period.name() << " = " << o.premium_video_is_grace_period << std::endl;
    os << o.guid.name() << " = " << o.guid << std::endl;
    os << o.dialog_partner.name() << " = " << o.dialog_partner << std::endl;
    os << o.meta_description.name() << " = " << o.meta_description << std::endl;
    os << o.premium_video_sponsor_list.name() << " = " << o.premium_video_sponsor_list << std::endl;
    os << o.mcr_caller.name() << " = " << o.mcr_caller << std::endl;
    os << o.chat_dbid.name() << " = " << o.chat_dbid << std::endl;
    os << o.history_horizon.name() << " = " << o.history_horizon << std::endl;
    os << o.history_sync_state.name() << " = " << o.history_sync_state << std::endl;
    os << o.is_blocked.name() << " = " << o.is_blocked << std::endl;
    os << o.last_message_id.name() << " = " << o.last_message_id << std::endl;
    os << o.picture.name() << " = " << o.picture << std::endl;
    os << o.is_p2p_migrated.name() << " = " << o.is_p2p_migrated << std::endl;
    os << o.thread_version.name() << " = " << o.thread_version << std::endl;
    os << o.consumption_horizon_set_at.name() << " = " << o.consumption_horizon_set_at << std::endl;
    os << o.alt_identity.name() << " = " << o.alt_identity << std::endl;
    os << o.in_migrated_thread_since.name() << " = " << o.in_migrated_thread_since << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Participants::Own::Id("id",A_field_type_integer,"Participants");
const std::string Participants::type__("Participants");
const std::string Participants::table__("Participants");
const std::string Participants::sequence__("Participants_seq");
const litesql::FieldType Participants::Id("id",A_field_type_integer,table__);
const litesql::FieldType Participants::Is_permanent("is_permanent",A_field_type_integer,table__);
const litesql::FieldType Participants::Convo_id("convo_id",A_field_type_integer,table__);
const litesql::FieldType Participants::Identity("identity",A_field_type_string,table__);
void Participants::initValues() {
}
void Participants::defaults() {
    id = 0;
    is_permanent = 0;
    convo_id = 0;
}
Participants::Participants(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), is_permanent(Is_permanent), convo_id(Convo_id), identity(Identity) {
    defaults();
}
Participants::Participants(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), is_permanent(Is_permanent), convo_id(Convo_id), identity(Identity) {
    defaults();
    size_t size = (rec.size() > 4) ? 4 : rec.size();
    switch(size) {
    case 4: identity = convert<const std::string&, std::string>(rec[3]);
        identity.setModified(false);
    case 3: convo_id = convert<const std::string&, int>(rec[2]);
        convo_id.setModified(false);
    case 2: is_permanent = convert<const std::string&, int>(rec[1]);
        is_permanent.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
Participants::Participants(const Participants& obj)
     : litesql::Persistent(obj), id(obj.id), is_permanent(obj.is_permanent), convo_id(obj.convo_id), identity(obj.identity) {
}
const Participants& Participants::operator=(const Participants& obj) {
    if (this != &obj) {
        id = obj.id;
        is_permanent = obj.is_permanent;
        convo_id = obj.convo_id;
        identity = obj.identity;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string Participants::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(is_permanent.name());
    values.push_back(is_permanent);
    is_permanent.setModified(false);
    fields.push_back(convo_id.name());
    values.push_back(convo_id);
    convo_id.setModified(false);
    fields.push_back(identity.name());
    values.push_back(identity);
    identity.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Participants::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    //Type processing disabled
    //type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Participants::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, is_permanent);
    updateField(updates, table__, convo_id);
    updateField(updates, table__, identity);
}
void Participants::addIDUpdates(Updates& updates) {
}
void Participants::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Is_permanent);
    ftypes.push_back(Convo_id);
    ftypes.push_back(Identity);
}
void Participants::delRecord() {
    deleteFromTable(table__, id);
}
void Participants::delRelations() {
}
void Participants::update() {
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
void Participants::del() {
    if (!typeIsCorrect()) {
        std::unique_ptr<Participants> p(upcastCopy());
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
bool Participants::typeIsCorrect() const {
    return true;
}
std::unique_ptr<Participants> Participants::upcast() const {
    return unique_ptr<Participants>(new Participants(*this));
}
std::unique_ptr<Participants> Participants::upcastCopy() const {
    Participants* np = new Participants(*this);
    np->id = id;
    np->is_permanent = is_permanent;
    np->convo_id = convo_id;
    np->identity = identity;
    np->inDatabase = inDatabase;
    return unique_ptr<Participants>(np);
}
std::ostream & operator<<(std::ostream& os, Participants o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.is_permanent.name() << " = " << o.is_permanent << std::endl;
    os << o.convo_id.name() << " = " << o.convo_id << std::endl;
    os << o.identity.name() << " = " << o.identity << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
main::main(std::string backendType, std::string connInfo)
     : litesql::Database(backendType, connInfo) {
    initialize();
}
std::vector<litesql::Database::SchemaItem> main::getSchema() const {
    vector<Database::SchemaItem> res;
    string TEXT = backend->getSQLType(A_field_type_string);
    string rowIdType = backend->getRowIDType();
    res.push_back(Database::SchemaItem("schema_","table","CREATE TABLE schema_ (name_ "+TEXT+", type_ "+TEXT+", sql_ "+TEXT+")"));
    if (backend->supportsSequences()) {
        res.push_back(Database::SchemaItem("Accounts_seq","sequence",backend->getCreateSequenceSQL("Accounts_seq")));
        res.push_back(Database::SchemaItem("Messages_seq","sequence",backend->getCreateSequenceSQL("Messages_seq")));
        res.push_back(Database::SchemaItem("Chats_seq","sequence",backend->getCreateSequenceSQL("Chats_seq")));
        res.push_back(Database::SchemaItem("Contacts_seq","sequence",backend->getCreateSequenceSQL("Contacts_seq")));
        res.push_back(Database::SchemaItem("Conversations_seq","sequence",backend->getCreateSequenceSQL("Conversations_seq")));
        res.push_back(Database::SchemaItem("Participants_seq","sequence",backend->getCreateSequenceSQL("Participants_seq")));
    }
    res.push_back(Database::SchemaItem("Accounts","table","CREATE TABLE Accounts (id " + rowIdType + ",skypename " + backend->getSQLType(A_field_type_string,"") + "" +",fullname " + backend->getSQLType(A_field_type_string,"") + "" +")"));
    res.push_back(Database::SchemaItem("Messages","table","CREATE TABLE Messages (id " + rowIdType + ",is_permanent " + backend->getSQLType(A_field_type_integer,"") + "" +",convo_id " + backend->getSQLType(A_field_type_integer,"") + "" +",chatname " + backend->getSQLType(A_field_type_string,"") + "" +",author " + backend->getSQLType(A_field_type_string,"") + "" +",from_dispname " + backend->getSQLType(A_field_type_string,"") + "" +",author_was_live " + backend->getSQLType(A_field_type_integer,"") + "" +",guid " + backend->getSQLType(A_field_type_blob,"") + "" +",dialog_partner " + backend->getSQLType(A_field_type_string,"") + "" +",timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +",sending_status " + backend->getSQLType(A_field_type_integer,"") + "" +",consumption_status " + backend->getSQLType(A_field_type_integer,"") + "" +",edited_by " + backend->getSQLType(A_field_type_string,"") + "" +",edited_timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +",param_key " + backend->getSQLType(A_field_type_integer,"") + "" +",param_value " + backend->getSQLType(A_field_type_integer,"") + "" +",body_xml " + backend->getSQLType(A_field_type_string,"") + "" +",identities " + backend->getSQLType(A_field_type_string,"") + "" +",reason " + backend->getSQLType(A_field_type_string,"") + "" +",leavereason " + backend->getSQLType(A_field_type_integer,"") + "" +",participant_count " + backend->getSQLType(A_field_type_integer,"") + "" +",error_code " + backend->getSQLType(A_field_type_integer,"") + "" +",chatmsg_type " + backend->getSQLType(A_field_type_integer,"") + "" +",chatmsg_status " + backend->getSQLType(A_field_type_integer,"") + "" +",body_is_rawxml " + backend->getSQLType(A_field_type_integer,"") + "" +",oldoptions " + backend->getSQLType(A_field_type_integer,"") + "" +",newoptions " + backend->getSQLType(A_field_type_integer,"") + "" +",newrole " + backend->getSQLType(A_field_type_integer,"") + "" +",pk_id " + backend->getSQLType(A_field_type_integer,"") + "" +",crc " + backend->getSQLType(A_field_type_integer,"") + "" +",remote_id " + backend->getSQLType(A_field_type_integer,"") + "" +",call_guid " + backend->getSQLType(A_field_type_string,"") + "" +")"));
    res.push_back(Database::SchemaItem("Chats","table","CREATE TABLE Chats (id " + rowIdType + ",is_permanent " + backend->getSQLType(A_field_type_integer,"") + "" +",name " + backend->getSQLType(A_field_type_string,"") + "" +",options " + backend->getSQLType(A_field_type_integer,"") + "" +",friendlyname " + backend->getSQLType(A_field_type_string,"") + "" +",description " + backend->getSQLType(A_field_type_string,"") + "" +",timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +",activity_timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +",dialog_partner " + backend->getSQLType(A_field_type_string,"") + "" +",adder " + backend->getSQLType(A_field_type_string,"") + "" +",mystatus " + backend->getSQLType(A_field_type_integer,"") + "" +",myrole " + backend->getSQLType(A_field_type_integer,"") + "" +",posters " + backend->getSQLType(A_field_type_string,"") + "" +",participants " + backend->getSQLType(A_field_type_string,"") + "" +",applicants " + backend->getSQLType(A_field_type_string,"") + "" +",banned_users " + backend->getSQLType(A_field_type_string,"") + "" +",name_text " + backend->getSQLType(A_field_type_string,"") + "" +",topic " + backend->getSQLType(A_field_type_string,"") + "" +",topic_xml " + backend->getSQLType(A_field_type_string,"") + "" +",guidelines " + backend->getSQLType(A_field_type_string,"") + "" +",picture " + backend->getSQLType(A_field_type_blob,"") + "" +",alertstring " + backend->getSQLType(A_field_type_string,"") + "" +",is_bookmarked " + backend->getSQLType(A_field_type_integer,"") + "" +",passwordhint " + backend->getSQLType(A_field_type_string,"") + "" +",unconsumed_suppressed_msg " + backend->getSQLType(A_field_type_integer,"") + "" +",unconsumed_normal_msg " + backend->getSQLType(A_field_type_integer,"") + "" +",unconsumed_elevated_msg " + backend->getSQLType(A_field_type_integer,"") + "" +",unconsumed_msg_voice " + backend->getSQLType(A_field_type_integer,"") + "" +",activemembers " + backend->getSQLType(A_field_type_string,"") + "" +",state_data " + backend->getSQLType(A_field_type_blob,"") + "" +",lifesigns " + backend->getSQLType(A_field_type_integer,"") + "" +",last_change " + backend->getSQLType(A_field_type_integer,"") + "" +",first_unread_message " + backend->getSQLType(A_field_type_integer,"") + "" +",pk_type " + backend->getSQLType(A_field_type_integer,"") + "" +",dbpath " + backend->getSQLType(A_field_type_string,"") + "" +",split_friendlyname " + backend->getSQLType(A_field_type_string,"") + "" +",conv_dbid " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("Contacts","table","CREATE TABLE Contacts (id " + rowIdType + ",is_permanent " + backend->getSQLType(A_field_type_integer,"") + "" +",skypename " + backend->getSQLType(A_field_type_string,"") + "" +",pstnnumber " + backend->getSQLType(A_field_type_string,"") + "" +",aliases " + backend->getSQLType(A_field_type_string,"") + "" +",fullname " + backend->getSQLType(A_field_type_string,"") + "" +",birthday " + backend->getSQLType(A_field_type_integer,"") + "" +",gender " + backend->getSQLType(A_field_type_integer,"") + "" +",languages " + backend->getSQLType(A_field_type_string,"") + "" +",country " + backend->getSQLType(A_field_type_string,"") + "" +",province " + backend->getSQLType(A_field_type_string,"") + "" +",city " + backend->getSQLType(A_field_type_string,"") + "" +",phone_home " + backend->getSQLType(A_field_type_string,"") + "" +",phone_office " + backend->getSQLType(A_field_type_string,"") + "" +",phone_mobile " + backend->getSQLType(A_field_type_string,"") + "" +",emails " + backend->getSQLType(A_field_type_string,"") + "" +",homepage " + backend->getSQLType(A_field_type_string,"") + "" +",about " + backend->getSQLType(A_field_type_string,"") + "" +",mood_text " + backend->getSQLType(A_field_type_string,"") + "" +",rich_mood_text " + backend->getSQLType(A_field_type_string,"") + "" +",timezone " + backend->getSQLType(A_field_type_integer,"") + "" +",profile_timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +",nrof_authed_buddies " + backend->getSQLType(A_field_type_integer,"") + "" +",ipcountry " + backend->getSQLType(A_field_type_string,"") + "" +",avatar_timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +",mood_timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +",received_authrequest " + backend->getSQLType(A_field_type_string,"") + "" +",authreq_timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +",lastonline_timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +",availability " + backend->getSQLType(A_field_type_integer,"") + "" +",displayname " + backend->getSQLType(A_field_type_string,"") + "" +",refreshing " + backend->getSQLType(A_field_type_integer,"") + "" +",given_authlevel " + backend->getSQLType(A_field_type_integer,"") + "" +",given_displayname " + backend->getSQLType(A_field_type_string,"") + "" +",assigned_speeddial " + backend->getSQLType(A_field_type_string,"") + "" +",assigned_comment " + backend->getSQLType(A_field_type_string,"") + "" +",alertstring " + backend->getSQLType(A_field_type_string,"") + "" +",lastused_timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +",authrequest_count " + backend->getSQLType(A_field_type_integer,"") + "" +",assigned_phone1 " + backend->getSQLType(A_field_type_string,"") + "" +",assigned_phone1_label " + backend->getSQLType(A_field_type_string,"") + "" +",assigned_phone2 " + backend->getSQLType(A_field_type_string,"") + "" +",assigned_phone2_label " + backend->getSQLType(A_field_type_string,"") + "" +",assigned_phone3 " + backend->getSQLType(A_field_type_string,"") + "" +",assigned_phone3_label " + backend->getSQLType(A_field_type_string,"") + "" +",buddystatus " + backend->getSQLType(A_field_type_integer,"") + "" +",isauthorized " + backend->getSQLType(A_field_type_integer,"") + "" +",popularity_ord " + backend->getSQLType(A_field_type_integer,"") + "" +",isblocked " + backend->getSQLType(A_field_type_integer,"") + "" +",certificate_send_count " + backend->getSQLType(A_field_type_integer,"") + "" +",account_modification_serial_nr " + backend->getSQLType(A_field_type_integer,"") + "" +",nr_of_buddies " + backend->getSQLType(A_field_type_integer,"") + "" +",server_synced " + backend->getSQLType(A_field_type_integer,"") + "" +",contactlist_track " + backend->getSQLType(A_field_type_integer,"") + "" +",last_used_networktime " + backend->getSQLType(A_field_type_integer,"") + "" +",authorized_time " + backend->getSQLType(A_field_type_integer,"") + "" +",sent_authrequest " + backend->getSQLType(A_field_type_string,"") + "" +",sent_authrequest_time " + backend->getSQLType(A_field_type_integer,"") + "" +",sent_authrequest_serial " + backend->getSQLType(A_field_type_integer,"") + "" +",node_capabilities " + backend->getSQLType(A_field_type_integer,"") + "" +",revoked_auth " + backend->getSQLType(A_field_type_integer,"") + "" +",added_in_shared_group " + backend->getSQLType(A_field_type_integer,"") + "" +",in_shared_group " + backend->getSQLType(A_field_type_integer,"") + "" +",stack_version " + backend->getSQLType(A_field_type_integer,"") + "" +",offline_authreq_id " + backend->getSQLType(A_field_type_integer,"") + "" +",node_capabilities_and " + backend->getSQLType(A_field_type_integer,"") + "" +",authreq_crc " + backend->getSQLType(A_field_type_integer,"") + "" +",authreq_src " + backend->getSQLType(A_field_type_integer,"") + "" +",pop_score " + backend->getSQLType(A_field_type_integer,"") + "" +",main_phone " + backend->getSQLType(A_field_type_string,"") + "" +",unified_servants " + backend->getSQLType(A_field_type_string,"") + "" +",phone_home_normalized " + backend->getSQLType(A_field_type_string,"") + "" +",phone_office_normalized " + backend->getSQLType(A_field_type_string,"") + "" +",phone_mobile_normalized " + backend->getSQLType(A_field_type_string,"") + "" +",sent_authrequest_initmethod " + backend->getSQLType(A_field_type_integer,"") + "" +",authreq_initmethod " + backend->getSQLType(A_field_type_integer,"") + "" +",sent_authrequest_extrasbitmask " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("Conversations","table","CREATE TABLE Conversations (id " + rowIdType + ",is_permanent " + backend->getSQLType(A_field_type_integer,"") + "" +",identity " + backend->getSQLType(A_field_type_string,"") + "" +",live_host " + backend->getSQLType(A_field_type_string,"") + "" +",live_start_timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +",live_is_muted " + backend->getSQLType(A_field_type_integer,"") + "" +",alert_string " + backend->getSQLType(A_field_type_string,"") + "" +",is_bookmarked " + backend->getSQLType(A_field_type_integer,"") + "" +",given_displayname " + backend->getSQLType(A_field_type_string,"") + "" +",displayname " + backend->getSQLType(A_field_type_string,"") + "" +",local_livestatus " + backend->getSQLType(A_field_type_integer,"") + "" +",inbox_timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +",inbox_message_id " + backend->getSQLType(A_field_type_integer,"") + "" +",unconsumed_suppressed_messages " + backend->getSQLType(A_field_type_integer,"") + "" +",unconsumed_normal_messages " + backend->getSQLType(A_field_type_integer,"") + "" +",unconsumed_elevated_messages " + backend->getSQLType(A_field_type_integer,"") + "" +",unconsumed_messages_voice " + backend->getSQLType(A_field_type_integer,"") + "" +",active_vm_id " + backend->getSQLType(A_field_type_integer,"") + "" +",context_horizon " + backend->getSQLType(A_field_type_integer,"") + "" +",consumption_horizon " + backend->getSQLType(A_field_type_integer,"") + "" +",last_activity_timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +",active_invoice_message " + backend->getSQLType(A_field_type_integer,"") + "" +",spawned_from_convo_id " + backend->getSQLType(A_field_type_integer,"") + "" +",pinned_order " + backend->getSQLType(A_field_type_integer,"") + "" +",creator " + backend->getSQLType(A_field_type_string,"") + "" +",creation_timestamp " + backend->getSQLType(A_field_type_integer,"") + "" +",my_status " + backend->getSQLType(A_field_type_integer,"") + "" +",opt_joining_enabled " + backend->getSQLType(A_field_type_integer,"") + "" +",opt_access_token " + backend->getSQLType(A_field_type_string,"") + "" +",opt_entry_level_rank " + backend->getSQLType(A_field_type_integer,"") + "" +",opt_disclose_history " + backend->getSQLType(A_field_type_integer,"") + "" +",opt_history_limit_in_days " + backend->getSQLType(A_field_type_integer,"") + "" +",opt_admin_only_activities " + backend->getSQLType(A_field_type_integer,"") + "" +",passwordhint " + backend->getSQLType(A_field_type_string,"") + "" +",meta_name " + backend->getSQLType(A_field_type_string,"") + "" +",meta_topic " + backend->getSQLType(A_field_type_string,"") + "" +",meta_guidelines " + backend->getSQLType(A_field_type_string,"") + "" +",meta_picture " + backend->getSQLType(A_field_type_blob,"") + "" +",premium_video_status " + backend->getSQLType(A_field_type_integer,"") + "" +",premium_video_is_grace_period " + backend->getSQLType(A_field_type_integer,"") + "" +",guid " + backend->getSQLType(A_field_type_string,"") + "" +",dialog_partner " + backend->getSQLType(A_field_type_string,"") + "" +",meta_description " + backend->getSQLType(A_field_type_string,"") + "" +",premium_video_sponsor_list " + backend->getSQLType(A_field_type_string,"") + "" +",mcr_caller " + backend->getSQLType(A_field_type_string,"") + "" +",chat_dbid " + backend->getSQLType(A_field_type_integer,"") + "" +",history_horizon " + backend->getSQLType(A_field_type_integer,"") + "" +",history_sync_state " + backend->getSQLType(A_field_type_string,"") + "" +",is_blocked " + backend->getSQLType(A_field_type_integer,"") + "" +",last_message_id " + backend->getSQLType(A_field_type_integer,"") + "" +",picture " + backend->getSQLType(A_field_type_string,"") + "" +",is_p2p_migrated " + backend->getSQLType(A_field_type_integer,"") + "" +",thread_version " + backend->getSQLType(A_field_type_string,"") + "" +",consumption_horizon_set_at " + backend->getSQLType(A_field_type_integer,"") + "" +",alt_identity " + backend->getSQLType(A_field_type_string,"") + "" +",in_migrated_thread_since " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("Participants","table","CREATE TABLE Participants (id " + rowIdType + ",is_permanent " + backend->getSQLType(A_field_type_integer,"") + "" +",convo_id " + backend->getSQLType(A_field_type_integer,"") + "" +",identity " + backend->getSQLType(A_field_type_string,"") + "" +")"));
    res.push_back(Database::SchemaItem("Accountsididx","index","CREATE INDEX Accountsididx ON Accounts (id)"));
    res.push_back(Database::SchemaItem("Messagesididx","index","CREATE INDEX Messagesididx ON Messages (id)"));
    res.push_back(Database::SchemaItem("Chatsididx","index","CREATE INDEX Chatsididx ON Chats (id)"));
    res.push_back(Database::SchemaItem("Contactsididx","index","CREATE INDEX Contactsididx ON Contacts (id)"));
    res.push_back(Database::SchemaItem("Conversationsididx","index","CREATE INDEX Conversationsididx ON Conversations (id)"));
    res.push_back(Database::SchemaItem("Participantsididx","index","CREATE INDEX Participantsididx ON Participants (id)"));
    return res;
}
void main::initialize() {
    static bool initialized = false;
    if (initialized)
        return;
    initialized = true;
}
}
