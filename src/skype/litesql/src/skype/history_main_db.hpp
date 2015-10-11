#ifndef history_main_db_hpp
#define history_main_db_hpp
#include "litesql.hpp"
namespace HistoryDB {
class Chats;
class ChatUsers;
class info;
class Messages;
class Users;
class Chats : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType Owner;
    litesql::Field<std::string> owner;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static const litesql::FieldType Creationtime;
    litesql::Field<int> creationtime;
    static void initValues();
protected:
    void defaults();
public:
    Chats(const litesql::Database& db);
    Chats(const litesql::Database& db, const litesql::Record& rec);
    Chats(const Chats& obj);
    const Chats& operator=(const Chats& obj);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<Chats> upcast() const;
    std::auto_ptr<Chats> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Chats o);
class ChatUsers : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType User_id;
    litesql::Field<int> user_id;
    static const litesql::FieldType Chat_id;
    litesql::Field<int> chat_id;
    static void initValues();
protected:
    void defaults();
public:
    ChatUsers(const litesql::Database& db);
    ChatUsers(const litesql::Database& db, const litesql::Record& rec);
    ChatUsers(const ChatUsers& obj);
    const ChatUsers& operator=(const ChatUsers& obj);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<ChatUsers> upcast() const;
    std::auto_ptr<ChatUsers> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, ChatUsers o);
class info : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType Dbversion;
    litesql::Field<int> dbversion;
    static void initValues();
protected:
    void defaults();
public:
    info(const litesql::Database& db);
    info(const litesql::Database& db, const litesql::Record& rec);
    info(const info& obj);
    const info& operator=(const info& obj);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<info> upcast() const;
    std::auto_ptr<info> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, info o);
class Messages : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType Body;
    litesql::Field<std::string> body;
    static const litesql::FieldType Chat_id;
    litesql::Field<int> chat_id;
    static const litesql::FieldType Timestamp;
    litesql::Field<int> timestamp;
    static const litesql::FieldType Sender_id;
    litesql::Field<int> sender_id;
    static const litesql::FieldType Skype_id;
    litesql::Field<int> skype_id;
    static const litesql::FieldType Skype_timestamp;
    litesql::Field<int> skype_timestamp;
    static void initValues();
protected:
    void defaults();
public:
    Messages(const litesql::Database& db);
    Messages(const litesql::Database& db, const litesql::Record& rec);
    Messages(const Messages& obj);
    const Messages& operator=(const Messages& obj);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<Messages> upcast() const;
    std::auto_ptr<Messages> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Messages o);
class Users : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType Displayname;
    litesql::Field<std::string> displayname;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static const litesql::FieldType Lastmessagetime;
    litesql::Field<int> lastmessagetime;
    static void initValues();
protected:
    void defaults();
public:
    Users(const litesql::Database& db);
    Users(const litesql::Database& db, const litesql::Record& rec);
    Users(const Users& obj);
    const Users& operator=(const Users& obj);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<Users> upcast() const;
    std::auto_ptr<Users> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Users o);
class history : public litesql::Database {
public:
    history(std::string backendType, std::string connInfo);
protected:
    virtual std::vector<litesql::Database::SchemaItem> getSchema() const;
    static void initialize();
};
}
#endif
