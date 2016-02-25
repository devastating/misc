enum msg_types
{
    CONN_REQ = 0,
    CONN_SUCCEED,
    CONN_REJ,
    CLIENT_TS,
    SRV_ACK
};

struct msg_hdr
{
    long type;
    long len;
};

struct conn_req_msg
{
    struct msg_hdr hdr;
    char name[256];
    char passwd[256];
};

struct client_ts_msg
{
    struct msg_hdr hdr;
    long ts_msb;
    long ts_lsb;
};

struct server_ack_msg
{
    struct msg_hdr hdr;
};

struct conn_succeed_msg
{
    struct msg_hdr hdr;
};


