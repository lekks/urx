#ifndef URX_BASECONNECTOR_H
#define URX_BASECONNECTOR_H


namespace urx {

    class ConnectorList;

    class BaseConnector {
        friend class ConnectorList;

        BaseConnector *next_connector = nullptr;
        ConnectorList *connectors = nullptr;

        BaseConnector &operator=(BaseConnector &) = delete;

        BaseConnector(BaseConnector &) = delete;

    public:
        BaseConnector(BaseConnector &&) = default;

        BaseConnector() {};

        virtual ~BaseConnector() {}

        inline bool is_connected() {
            return connectors != nullptr;
        };
    };

    class ConnectorList {
        BaseConnector *first_connector;

        static void append_connector(BaseConnector *&dst, BaseConnector *connector) {
            if (dst && (dst != connector)) { // рекурсия для поиска дубликатов
                append_connector(dst->next_connector, connector);
            } else {
                dst = connector;
            }
        };

        static void remove_connector(BaseConnector *&dst, BaseConnector *connector) {
            if (dst) {
                if (dst == connector) {
                    dst = connector->next_connector;
                    connector->next_connector = 0;
                    connector->next_connector = 0;
                } else {
                    remove_connector(dst->next_connector, connector);
                }
            }
        };
    public:
        ConnectorList() : first_connector(0) {};

        ~ConnectorList() {
            remove_all();
        };

        inline BaseConnector *first_conn() const {
            return first_connector;
        }

        inline BaseConnector *next_conn(BaseConnector *connector) const {
            return connector->next_connector;
        }

        void add(BaseConnector *plug) {
            if (plug->next_connector)
                plug->connectors->remove(plug);
            append_connector(first_connector, plug);
            plug->connectors = this;
        };

        void remove(BaseConnector *plug) {
            remove_connector(first_connector, plug);
        };

        void remove_all() {}// TODO
    };


//*****************************************************


}

#endif // PORT_BASE

