#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <random>
#include <condition_variable>
using namespace std;

/*
    Customer service system:
    Write a program that simulates the way customers are
    served in an office. The office has three desks where
    customers can be served at the same time. Customers
    can enter the office at any time. They take a ticket
    with a service number from a ticketing machine and
    wait until their number is next for service at one of
    the desks. Customers are served in the order they entered
    the office, or more precisely, in the order given by their
    ticket. Every time a service desk finishes serving a
    customer, the next customer in order is served. The
    simulation should stop after a particular number of
    customers have been issued tickets and served.
*/
struct Customer
{
    int m_number;
    explicit Customer(int mNumber) : m_number(mNumber)
    {}
};

struct HelpDeskMonitor
{
    queue<Customer> m_tickets;
    condition_variable m_cv;
    mutex m_mut;
    bool m_customerAvail{false};
    bool m_isOnDuty{false};
    thread m_monitor;
    thread m_desk1;
    thread m_desk2;
    thread m_desk3;

    HelpDeskMonitor() = default;
    ~HelpDeskMonitor()
    {
        m_monitor.join();
        m_desk1.join();
        m_desk2.join();
        m_desk3.join();
    };


    void waitForCus(int desk)
    {
        this_thread::sleep_for(5s);
        while (m_isOnDuty)
        {
            unique_lock<mutex> lck(m_mut);
            cout << "Desk " << desk << " waiting." << endl;
            m_cv.wait(lck, [&] { return m_customerAvail; });

            if (!m_tickets.empty())
            {
                auto customer = m_tickets.front();
                m_tickets.pop();
                lck.unlock();
                processCustomer(desk, customer);
            } else
            {
                lck.unlock();
                continue;
            }
        }
    }

    void processCustomer(int tId, Customer &c) const
    {
        random_device rd;
        uniform_int_distribution dis(500, 3000);
        mt19937 gen(rd());
        int val = dis(gen);
        this_thread::sleep_for(chrono::milliseconds(val));
        cout << "Desk " << tId << ": Processing customer: " << c.m_number << " , time taken: " << val / static_cast<double>(1000) << "s" << endl;
    }

    void addCustomer(Customer &&cus)
    {
        if (m_isOnDuty)
        {
            m_tickets.push(cus);
            if (!m_customerAvail) m_customerAvail = true;
            m_cv.notify_one();
        } else
            cout << "Nobody is on duty come back later." << endl;
    }

    void start()
    {

        m_monitor = thread([&] {
            cout << "Manager on duty..." << endl;
            m_isOnDuty = true;
            while (true)
            {
                if (m_tickets.empty())
                {
                    m_customerAvail = false;
                } else
                {
                    m_customerAvail = true;
                    m_cv.notify_one();
                }
            }
        });

        m_desk1 = thread([&] { waitForCus(1); });
        m_desk2 = thread([&] { waitForCus(2); });
        m_desk3 = thread([&] { waitForCus(3); });

    }

};


int main()
{
    HelpDeskMonitor desk;
    desk.start();
    random_device rd;
    uniform_int_distribution dis(100, 1000);
    mt19937 gen(rd());


    for (auto i{0}; i < 100; i++)
    {
        this_thread::sleep_for(chrono::milliseconds(dis(gen)));
        desk.addCustomer(Customer(1 + i));
    }

    return 0;
}
