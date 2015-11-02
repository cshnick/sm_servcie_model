#ifndef skype_main_db_hpp
#define skype_main_db_hpp
#include "litesql.hpp"
namespace SkypeDB {
class Accounts;
class Messages;
class Chats;
class Contacts;
class Conversations;
class Participants;
class Accounts : public litesql::Persistent {
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
    static const litesql::FieldType Skypename;
    litesql::Field<std::string> skypename;
    static const litesql::FieldType Fullname;
    litesql::Field<std::string> fullname;
    static void initValues();
protected:
    void defaults();
public:
    Accounts(const litesql::Database& db);
    Accounts(const litesql::Database& db, const litesql::Record& rec);
    Accounts(const Accounts& obj);
    const Accounts& operator=(const Accounts& obj);
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
    std::unique_ptr<Accounts> upcast() const;
    std::unique_ptr<Accounts> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Accounts o);
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
    static const litesql::FieldType Is_permanent;
    litesql::Field<int> is_permanent;
    static const litesql::FieldType Convo_id;
    litesql::Field<int> convo_id;
    static const litesql::FieldType Chatname;
    litesql::Field<std::string> chatname;
    static const litesql::FieldType Author;
    litesql::Field<std::string> author;
    static const litesql::FieldType From_dispname;
    litesql::Field<std::string> from_dispname;
    static const litesql::FieldType Author_was_live;
    litesql::Field<int> author_was_live;
    static const litesql::FieldType Guid;
    litesql::Field<litesql::Blob> guid;
    static const litesql::FieldType Dialog_partner;
    litesql::Field<std::string> dialog_partner;
    static const litesql::FieldType Timestamp;
    litesql::Field<int> timestamp;
    static const litesql::FieldType Sending_status;
    litesql::Field<int> sending_status;
    static const litesql::FieldType Consumption_status;
    litesql::Field<int> consumption_status;
    static const litesql::FieldType Edited_by;
    litesql::Field<std::string> edited_by;
    static const litesql::FieldType Edited_timestamp;
    litesql::Field<int> edited_timestamp;
    static const litesql::FieldType Param_key;
    litesql::Field<int> param_key;
    static const litesql::FieldType Param_value;
    litesql::Field<int> param_value;
    static const litesql::FieldType Body_xml;
    litesql::Field<std::string> body_xml;
    static const litesql::FieldType Identities;
    litesql::Field<std::string> identities;
    static const litesql::FieldType Reason;
    litesql::Field<std::string> reason;
    static const litesql::FieldType Leavereason;
    litesql::Field<int> leavereason;
    static const litesql::FieldType Participant_count;
    litesql::Field<int> participant_count;
    static const litesql::FieldType Error_code;
    litesql::Field<int> error_code;
    static const litesql::FieldType Chatmsg_type;
    litesql::Field<int> chatmsg_type;
    static const litesql::FieldType Chatmsg_status;
    litesql::Field<int> chatmsg_status;
    static const litesql::FieldType Body_is_rawxml;
    litesql::Field<int> body_is_rawxml;
    static const litesql::FieldType Oldoptions;
    litesql::Field<int> oldoptions;
    static const litesql::FieldType Newoptions;
    litesql::Field<int> newoptions;
    static const litesql::FieldType Newrole;
    litesql::Field<int> newrole;
    static const litesql::FieldType Pk_id;
    litesql::Field<int> pk_id;
    static const litesql::FieldType Crc;
    litesql::Field<int> crc;
    static const litesql::FieldType Remote_id;
    litesql::Field<int> remote_id;
    static const litesql::FieldType Call_guid;
    litesql::Field<std::string> call_guid;
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
    std::unique_ptr<Messages> upcast() const;
    std::unique_ptr<Messages> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Messages o);
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
    static const litesql::FieldType Is_permanent;
    litesql::Field<int> is_permanent;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static const litesql::FieldType Options;
    litesql::Field<int> options;
    static const litesql::FieldType Friendlyname;
    litesql::Field<std::string> friendlyname;
    static const litesql::FieldType Description;
    litesql::Field<std::string> description;
    static const litesql::FieldType Timestamp;
    litesql::Field<int> timestamp;
    static const litesql::FieldType Activity_timestamp;
    litesql::Field<int> activity_timestamp;
    static const litesql::FieldType Dialog_partner;
    litesql::Field<std::string> dialog_partner;
    static const litesql::FieldType Adder;
    litesql::Field<std::string> adder;
    static const litesql::FieldType Mystatus;
    litesql::Field<int> mystatus;
    static const litesql::FieldType Myrole;
    litesql::Field<int> myrole;
    static const litesql::FieldType Posters;
    litesql::Field<std::string> posters;
    static const litesql::FieldType Participants;
    litesql::Field<std::string> participants;
    static const litesql::FieldType Applicants;
    litesql::Field<std::string> applicants;
    static const litesql::FieldType Banned_users;
    litesql::Field<std::string> banned_users;
    static const litesql::FieldType Name_text;
    litesql::Field<std::string> name_text;
    static const litesql::FieldType Topic;
    litesql::Field<std::string> topic;
    static const litesql::FieldType Topic_xml;
    litesql::Field<std::string> topic_xml;
    static const litesql::FieldType Guidelines;
    litesql::Field<std::string> guidelines;
    static const litesql::FieldType Picture;
    litesql::Field<litesql::Blob> picture;
    static const litesql::FieldType Alertstring;
    litesql::Field<std::string> alertstring;
    static const litesql::FieldType Is_bookmarked;
    litesql::Field<int> is_bookmarked;
    static const litesql::FieldType Passwordhint;
    litesql::Field<std::string> passwordhint;
    static const litesql::FieldType Unconsumed_suppressed_msg;
    litesql::Field<int> unconsumed_suppressed_msg;
    static const litesql::FieldType Unconsumed_normal_msg;
    litesql::Field<int> unconsumed_normal_msg;
    static const litesql::FieldType Unconsumed_elevated_msg;
    litesql::Field<int> unconsumed_elevated_msg;
    static const litesql::FieldType Unconsumed_msg_voice;
    litesql::Field<int> unconsumed_msg_voice;
    static const litesql::FieldType Activemembers;
    litesql::Field<std::string> activemembers;
    static const litesql::FieldType State_data;
    litesql::Field<litesql::Blob> state_data;
    static const litesql::FieldType Lifesigns;
    litesql::Field<int> lifesigns;
    static const litesql::FieldType Last_change;
    litesql::Field<int> last_change;
    static const litesql::FieldType First_unread_message;
    litesql::Field<int> first_unread_message;
    static const litesql::FieldType Pk_type;
    litesql::Field<int> pk_type;
    static const litesql::FieldType Dbpath;
    litesql::Field<std::string> dbpath;
    static const litesql::FieldType Split_friendlyname;
    litesql::Field<std::string> split_friendlyname;
    static const litesql::FieldType Conv_dbid;
    litesql::Field<int> conv_dbid;
    static void initValues();
protected:
    void defaults();
public:
    Chats(const litesql::Database& db);
    Chats(const litesql::Database& db, const litesql::Record& rec);
    Chats(const Chats& obj);
    const Chats& operator=(const Chats& obj);
    virtual litesql::Field<std::string> Chats::* cache_field();
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
    std::unique_ptr<Chats> upcast() const;
    std::unique_ptr<Chats> upcastCopy() const;
    typedef std::string cache_key_type;
};
std::ostream & operator<<(std::ostream& os, Chats o);
class Contacts : public litesql::Persistent {
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
    static const litesql::FieldType Is_permanent;
    litesql::Field<int> is_permanent;
    static const litesql::FieldType Skypename;
    litesql::Field<std::string> skypename;
    static const litesql::FieldType Pstnnumber;
    litesql::Field<std::string> pstnnumber;
    static const litesql::FieldType Aliases;
    litesql::Field<std::string> aliases;
    static const litesql::FieldType Fullname;
    litesql::Field<std::string> fullname;
    static const litesql::FieldType Birthday;
    litesql::Field<int> birthday;
    static const litesql::FieldType Gender;
    litesql::Field<int> gender;
    static const litesql::FieldType Languages;
    litesql::Field<std::string> languages;
    static const litesql::FieldType Country;
    litesql::Field<std::string> country;
    static const litesql::FieldType Province;
    litesql::Field<std::string> province;
    static const litesql::FieldType City;
    litesql::Field<std::string> city;
    static const litesql::FieldType Phone_home;
    litesql::Field<std::string> phone_home;
    static const litesql::FieldType Phone_office;
    litesql::Field<std::string> phone_office;
    static const litesql::FieldType Phone_mobile;
    litesql::Field<std::string> phone_mobile;
    static const litesql::FieldType Emails;
    litesql::Field<std::string> emails;
    static const litesql::FieldType Hashed_emails;
    litesql::Field<std::string> hashed_emails;
    static const litesql::FieldType Homepage;
    litesql::Field<std::string> homepage;
    static const litesql::FieldType About;
    litesql::Field<std::string> about;
    static const litesql::FieldType Mood_text;
    litesql::Field<std::string> mood_text;
    static const litesql::FieldType Rich_mood_text;
    litesql::Field<std::string> rich_mood_text;
    static const litesql::FieldType Timezone;
    litesql::Field<int> timezone;
    static const litesql::FieldType Profile_timestamp;
    litesql::Field<int> profile_timestamp;
    static const litesql::FieldType Nrof_authed_buddies;
    litesql::Field<int> nrof_authed_buddies;
    static const litesql::FieldType Ipcountry;
    litesql::Field<std::string> ipcountry;
    static const litesql::FieldType Avatar_timestamp;
    litesql::Field<int> avatar_timestamp;
    static const litesql::FieldType Mood_timestamp;
    litesql::Field<int> mood_timestamp;
    static const litesql::FieldType Received_authrequest;
    litesql::Field<std::string> received_authrequest;
    static const litesql::FieldType Authreq_timestamp;
    litesql::Field<int> authreq_timestamp;
    static const litesql::FieldType Lastonline_timestamp;
    litesql::Field<int> lastonline_timestamp;
    static const litesql::FieldType Availability;
    litesql::Field<int> availability;
    static const litesql::FieldType Displayname;
    litesql::Field<std::string> displayname;
    static const litesql::FieldType Refreshing;
    litesql::Field<int> refreshing;
    static const litesql::FieldType Given_authlevel;
    litesql::Field<int> given_authlevel;
    static const litesql::FieldType Given_displayname;
    litesql::Field<std::string> given_displayname;
    static const litesql::FieldType Assigned_speeddial;
    litesql::Field<std::string> assigned_speeddial;
    static const litesql::FieldType Assigned_comment;
    litesql::Field<std::string> assigned_comment;
    static const litesql::FieldType Alertstring;
    litesql::Field<std::string> alertstring;
    static const litesql::FieldType Lastused_timestamp;
    litesql::Field<int> lastused_timestamp;
    static const litesql::FieldType Authrequest_count;
    litesql::Field<int> authrequest_count;
    static const litesql::FieldType Assigned_phone1;
    litesql::Field<std::string> assigned_phone1;
    static const litesql::FieldType Assigned_phone1_label;
    litesql::Field<std::string> assigned_phone1_label;
    static const litesql::FieldType Assigned_phone2;
    litesql::Field<std::string> assigned_phone2;
    static const litesql::FieldType Assigned_phone2_label;
    litesql::Field<std::string> assigned_phone2_label;
    static const litesql::FieldType Assigned_phone3;
    litesql::Field<std::string> assigned_phone3;
    static const litesql::FieldType Assigned_phone3_label;
    litesql::Field<std::string> assigned_phone3_label;
    static const litesql::FieldType Buddystatus;
    litesql::Field<int> buddystatus;
    static const litesql::FieldType Isauthorized;
    litesql::Field<int> isauthorized;
    static const litesql::FieldType Popularity_ord;
    litesql::Field<int> popularity_ord;
    static const litesql::FieldType External_id;
    litesql::Field<std::string> external_id;
    static const litesql::FieldType External_system_id;
    litesql::Field<std::string> external_system_id;
    static const litesql::FieldType Isblocked;
    litesql::Field<int> isblocked;
    static const litesql::FieldType Certificate_send_count;
    litesql::Field<int> certificate_send_count;
    static const litesql::FieldType Account_modification_serial_nr;
    litesql::Field<int> account_modification_serial_nr;
    static const litesql::FieldType Nr_of_buddies;
    litesql::Field<int> nr_of_buddies;
    static const litesql::FieldType Server_synced;
    litesql::Field<int> server_synced;
    static const litesql::FieldType Contactlist_track;
    litesql::Field<int> contactlist_track;
    static const litesql::FieldType Last_used_networktime;
    litesql::Field<int> last_used_networktime;
    static const litesql::FieldType Authorized_time;
    litesql::Field<int> authorized_time;
    static const litesql::FieldType Sent_authrequest;
    litesql::Field<std::string> sent_authrequest;
    static const litesql::FieldType Sent_authrequest_time;
    litesql::Field<int> sent_authrequest_time;
    static const litesql::FieldType Sent_authrequest_serial;
    litesql::Field<int> sent_authrequest_serial;
    static const litesql::FieldType Node_capabilities;
    litesql::Field<int> node_capabilities;
    static const litesql::FieldType Revoked_auth;
    litesql::Field<int> revoked_auth;
    static const litesql::FieldType Added_in_shared_group;
    litesql::Field<int> added_in_shared_group;
    static const litesql::FieldType In_shared_group;
    litesql::Field<int> in_shared_group;
    static const litesql::FieldType Stack_version;
    litesql::Field<int> stack_version;
    static const litesql::FieldType Offline_authreq_id;
    litesql::Field<int> offline_authreq_id;
    static const litesql::FieldType Node_capabilities_and;
    litesql::Field<int> node_capabilities_and;
    static const litesql::FieldType Authreq_crc;
    litesql::Field<int> authreq_crc;
    static const litesql::FieldType Authreq_src;
    litesql::Field<int> authreq_src;
    static const litesql::FieldType Pop_score;
    litesql::Field<int> pop_score;
    static const litesql::FieldType Main_phone;
    litesql::Field<std::string> main_phone;
    static const litesql::FieldType Unified_servants;
    litesql::Field<std::string> unified_servants;
    static const litesql::FieldType Phone_home_normalized;
    litesql::Field<std::string> phone_home_normalized;
    static const litesql::FieldType Phone_office_normalized;
    litesql::Field<std::string> phone_office_normalized;
    static const litesql::FieldType Phone_mobile_normalized;
    litesql::Field<std::string> phone_mobile_normalized;
    static const litesql::FieldType Sent_authrequest_initmethod;
    litesql::Field<int> sent_authrequest_initmethod;
    static const litesql::FieldType Authreq_initmethod;
    litesql::Field<int> authreq_initmethod;
    static const litesql::FieldType Sent_authrequest_extrasbitmask;
    litesql::Field<int> sent_authrequest_extrasbitmask;
    static const litesql::FieldType Liveid_cid;
    litesql::Field<std::string> liveid_cid;
    static void initValues();
protected:
    void defaults();
public:
    Contacts(const litesql::Database& db);
    Contacts(const litesql::Database& db, const litesql::Record& rec);
    Contacts(const Contacts& obj);
    const Contacts& operator=(const Contacts& obj);
    virtual litesql::Field<std::string> Contacts::* cache_field();
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
    std::unique_ptr<Contacts> upcast() const;
    std::unique_ptr<Contacts> upcastCopy() const;
    typedef std::string cache_key_type;
};
std::ostream & operator<<(std::ostream& os, Contacts o);
class Conversations : public litesql::Persistent {
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
    static const litesql::FieldType Is_permanent;
    litesql::Field<int> is_permanent;
    static const litesql::FieldType Identity;
    litesql::Field<std::string> identity;
    static const litesql::FieldType Live_host;
    litesql::Field<std::string> live_host;
    static const litesql::FieldType Live_start_timestamp;
    litesql::Field<int> live_start_timestamp;
    static const litesql::FieldType Live_is_muted;
    litesql::Field<int> live_is_muted;
    static const litesql::FieldType Alert_string;
    litesql::Field<std::string> alert_string;
    static const litesql::FieldType Is_bookmarked;
    litesql::Field<int> is_bookmarked;
    static const litesql::FieldType Given_displayname;
    litesql::Field<std::string> given_displayname;
    static const litesql::FieldType Displayname;
    litesql::Field<std::string> displayname;
    static const litesql::FieldType Local_livestatus;
    litesql::Field<int> local_livestatus;
    static const litesql::FieldType Inbox_timestamp;
    litesql::Field<int> inbox_timestamp;
    static const litesql::FieldType Inbox_message_id;
    litesql::Field<int> inbox_message_id;
    static const litesql::FieldType Unconsumed_suppressed_messages;
    litesql::Field<int> unconsumed_suppressed_messages;
    static const litesql::FieldType Unconsumed_normal_messages;
    litesql::Field<int> unconsumed_normal_messages;
    static const litesql::FieldType Unconsumed_elevated_messages;
    litesql::Field<int> unconsumed_elevated_messages;
    static const litesql::FieldType Unconsumed_messages_voice;
    litesql::Field<int> unconsumed_messages_voice;
    static const litesql::FieldType Active_vm_id;
    litesql::Field<int> active_vm_id;
    static const litesql::FieldType Context_horizon;
    litesql::Field<int> context_horizon;
    static const litesql::FieldType Consumption_horizon;
    litesql::Field<int> consumption_horizon;
    static const litesql::FieldType Last_activity_timestamp;
    litesql::Field<int> last_activity_timestamp;
    static const litesql::FieldType Active_invoice_message;
    litesql::Field<int> active_invoice_message;
    static const litesql::FieldType Spawned_from_convo_id;
    litesql::Field<int> spawned_from_convo_id;
    static const litesql::FieldType Pinned_order;
    litesql::Field<int> pinned_order;
    static const litesql::FieldType Creator;
    litesql::Field<std::string> creator;
    static const litesql::FieldType Creation_timestamp;
    litesql::Field<int> creation_timestamp;
    static const litesql::FieldType My_status;
    litesql::Field<int> my_status;
    static const litesql::FieldType Opt_joining_enabled;
    litesql::Field<int> opt_joining_enabled;
    static const litesql::FieldType Opt_access_token;
    litesql::Field<std::string> opt_access_token;
    static const litesql::FieldType Opt_entry_level_rank;
    litesql::Field<int> opt_entry_level_rank;
    static const litesql::FieldType Opt_disclose_history;
    litesql::Field<int> opt_disclose_history;
    static const litesql::FieldType Opt_history_limit_in_days;
    litesql::Field<int> opt_history_limit_in_days;
    static const litesql::FieldType Opt_admin_only_activities;
    litesql::Field<int> opt_admin_only_activities;
    static const litesql::FieldType Passwordhint;
    litesql::Field<std::string> passwordhint;
    static const litesql::FieldType Meta_name;
    litesql::Field<std::string> meta_name;
    static const litesql::FieldType Meta_topic;
    litesql::Field<std::string> meta_topic;
    static const litesql::FieldType Meta_guidelines;
    litesql::Field<std::string> meta_guidelines;
    static const litesql::FieldType Meta_picture;
    litesql::Field<litesql::Blob> meta_picture;
    static const litesql::FieldType Premium_video_status;
    litesql::Field<int> premium_video_status;
    static const litesql::FieldType Premium_video_is_grace_period;
    litesql::Field<int> premium_video_is_grace_period;
    static const litesql::FieldType Guid;
    litesql::Field<std::string> guid;
    static const litesql::FieldType Dialog_partner;
    litesql::Field<std::string> dialog_partner;
    static const litesql::FieldType Meta_description;
    litesql::Field<std::string> meta_description;
    static const litesql::FieldType Premium_video_sponsor_list;
    litesql::Field<std::string> premium_video_sponsor_list;
    static const litesql::FieldType Mcr_caller;
    litesql::Field<std::string> mcr_caller;
    static const litesql::FieldType Chat_dbid;
    litesql::Field<int> chat_dbid;
    static const litesql::FieldType History_horizon;
    litesql::Field<int> history_horizon;
    static const litesql::FieldType History_sync_state;
    litesql::Field<std::string> history_sync_state;
    static const litesql::FieldType Is_blocked;
    litesql::Field<int> is_blocked;
    static const litesql::FieldType Last_message_id;
    litesql::Field<int> last_message_id;
    static const litesql::FieldType Picture;
    litesql::Field<std::string> picture;
    static const litesql::FieldType Is_p2p_migrated;
    litesql::Field<int> is_p2p_migrated;
    static const litesql::FieldType Thread_version;
    litesql::Field<std::string> thread_version;
    static const litesql::FieldType Consumption_horizon_set_at;
    litesql::Field<int> consumption_horizon_set_at;
    static const litesql::FieldType Alt_identity;
    litesql::Field<std::string> alt_identity;
    static const litesql::FieldType In_migrated_thread_since;
    litesql::Field<int> in_migrated_thread_since;
    static void initValues();
protected:
    void defaults();
public:
    Conversations(const litesql::Database& db);
    Conversations(const litesql::Database& db, const litesql::Record& rec);
    Conversations(const Conversations& obj);
    const Conversations& operator=(const Conversations& obj);
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
    std::unique_ptr<Conversations> upcast() const;
    std::unique_ptr<Conversations> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Conversations o);
class Participants : public litesql::Persistent {
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
    static const litesql::FieldType Is_permanent;
    litesql::Field<int> is_permanent;
    static const litesql::FieldType Convo_id;
    litesql::Field<int> convo_id;
    static const litesql::FieldType Identity;
    litesql::Field<std::string> identity;
    static void initValues();
protected:
    void defaults();
public:
    Participants(const litesql::Database& db);
    Participants(const litesql::Database& db, const litesql::Record& rec);
    Participants(const Participants& obj);
    const Participants& operator=(const Participants& obj);
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
    std::unique_ptr<Participants> upcast() const;
    std::unique_ptr<Participants> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Participants o);
class main : public litesql::Database {
public:
    main(std::string backendType, std::string connInfo);
protected:
    virtual std::vector<litesql::Database::SchemaItem> getSchema() const;
    static void initialize();
};
}
#endif
