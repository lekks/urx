#ifndef URX_OBSERVER_BASE_HPP
#define URX_OBSERVER_BASE_HPP


namespace urx {

    class ObserversList;

    class ObserverBase {
        friend class ObserversList;

        ObserverBase *next_connector = nullptr;
        ObserversList *connectors = nullptr;
    public:
        ObserverBase &operator=(ObserverBase &) = delete;

        ObserverBase(ObserverBase &) = delete;

        ObserverBase(ObserverBase &&) = default;

        ObserverBase() = default;

        virtual ~ObserverBase() = default;

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
        ObserversList() : first_connector(nullptr) {};

        ~ObserversList() {
            remove_all();
        };

        inline ObserverBase *first_conn() const {
            return first_connector;
        }

        static inline ObserverBase *next_conn(ObserverBase *connector) {
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

}

#endif // URX_OBSERVER_BASE_HPP

