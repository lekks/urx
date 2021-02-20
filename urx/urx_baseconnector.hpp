#ifndef URX_BASECONNECTOR_H
#define URX_BASECONNECTOR_H


namespace urx {

    class ObserversList;

    class ObserverBase {
        friend class ObserversList;

        ObserverBase *next_connector = nullptr;
        ObserversList *connectors = nullptr;

        ObserverBase &operator=(ObserverBase &) = delete;

        ObserverBase(ObserverBase &) = delete;

    public:
        ObserverBase(ObserverBase &&) = default;

        ObserverBase() {};

        virtual ~ObserverBase() {}

        inline bool is_connected() {
            return connectors != nullptr;
        };
    };

    class ObserversList {
        ObserverBase *first_connector;

        static void append_connector(ObserverBase *&dst, ObserverBase *connector) {
            if (dst && (dst != connector)) { // рекурсия для поиска дубликатов
                append_connector(dst->next_connector, connector);
            } else {
                dst = connector;
            }
        };

        static void remove_connector(ObserverBase *&dst, ObserverBase *connector) {
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
        ObserversList() : first_connector(0) {};

        ~ObserversList() {
            remove_all();
        };

        inline ObserverBase *first_conn() const {
            return first_connector;
        }

        inline ObserverBase *next_conn(ObserverBase *connector) const {
            return connector->next_connector;
        }

        void add(ObserverBase *plug) {
            if (plug->next_connector)
                plug->connectors->remove(plug);
            append_connector(first_connector, plug);
            plug->connectors = this;
        };

        void remove(ObserverBase *plug) {
            remove_connector(first_connector, plug);
        };

        void remove_all() {}// TODO
    };


//*****************************************************


}

#endif // PORT_BASE

