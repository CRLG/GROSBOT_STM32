#ifndef _ASSERV_LOGGER_H_
#define _ASSERV_LOGGER_H_


class CAsservLogger
{
public:
    CAsservLogger();

    void start();
    void stop();
    bool step();
    void print();

    bool m_started;
    long m_start_time;
    long m_index;       // Pointe toujours sur la prochaine ligne
    bool m_rollback_until_convergence;
};

#endif // _ASSERV_LOGGER_H_
