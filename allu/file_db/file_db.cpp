#include <string>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

struct order
{
    long orderID;
    char owner[32];
    long amount;
};

class file_db
{
    public:
        explicit file_db(string db_file_name)
        {
            m_db_file = db_file_name;
            // Memory buffer
            m_order_buffer = new order[m_order_buffer_size];
        }
        ~file_db()
        {
            delete [] m_order_buffer;
        }
        bool insert_order(const order *new_order)
        {
            if (!new_order) return false;

            // First try to see if a record with the same ID existing
            order tmp_order;
            int order_offset = search_order(new_order->orderID, &tmp_order);
            if (order_offset != -1)
            {
                cout << "An order with same orderID " << new_order->orderID << " existing\n";
                return false;
            }

            auto fp = fopen(m_db_file.c_str(), "ab+");
            if (!fp) return -1;

            // Move all the way to the end
            fseek(fp, 0, SEEK_END);
            auto written = fwrite(new_order, sizeof(order), 1, fp);
            if (written != 1)
            {
                cout << "Fucking error insert\n";
            }
            fflush(fp);

            fclose(fp);
            return true;
        }
        bool update_order(order *to_update_order)
        {
            if (!to_update_order) return false;
            // First try to see if a record with the same ID existing
            order tmp_order;
            int order_offset = search_order(to_update_order->orderID, &tmp_order);
            if (order_offset == -1)
            {
                cout << "No order with orderID existing\n";
                return false;
            }
            auto fp = fopen(m_db_file.c_str(), "rb+");
            if (!fp) return -1;

            // Move all the way to the target
            fseek(fp, sizeof(order) * order_offset, SEEK_SET);
            auto written = fwrite(to_update_order, sizeof(order), 1, fp);
            if (written != 1)
            {
                cout << "Fucking error update\n";
                assert(false);
            }
            fflush(fp);

            fclose(fp);
            return true;
        }
        int read_order(order *out, int offset, int to_read)
        {
            if (!out) return -1;

            auto fp = fopen(m_db_file.c_str(), "rb+");
            if (!fp) return -1;

            // Move to the beginning of interesting order
            fseek(fp, offset * sizeof(order), SEEK_SET);
            int read_record = fread(out, sizeof(order),
                                    to_read, fp);
            // Return # of records actually read
            return read_record;
        }
        int search_order(long target, order *out)
        {
            if (!out) return -1;

            auto fp = fopen(m_db_file.c_str(), "rb+");
            if (!fp) return -1;

            int recorder_offset = 0;
            bool found = false;

            while (found == false)
            {
                int records = fread(m_order_buffer, sizeof(order),
                                    m_order_buffer_size, fp);
                if (records == 0)
                {
                    break;
                }
                for (int i = 0; i < records; i++)
                {
                    if (m_order_buffer[i].orderID == target)
                    {
                        // Found record
                        memcpy(out, &m_order_buffer[i], sizeof(order));
                        found = true;
                        break;
                    }
                    recorder_offset++;
                }
            }
            fclose(fp);
            return found? recorder_offset: (-1);
        }
    private:
        string m_db_file;
        int m_order_buffer_size = 32;
        order *m_order_buffer;
};

void remove_db_file(string db_file)
{
    // Remove stale previous test DB
    string cmd = "rm -rf ";
    cmd += db_file;
    system(cmd.c_str());
}

void test_insert_read()
{
    string file_db_name = "test_db_file.db";
    // Remove stale previous test DB
    remove_db_file(file_db_name);

    file_db fdb(file_db_name);
    for (int i = 0; i < 1000; i++)
    {
        order new_order;
        new_order.orderID = 50 + i;
        new_order.amount = 10 + i;
        memset(new_order.owner, 'a' + i % 26, sizeof(new_order.owner));
        fdb.insert_order(&new_order);
    }

    // Test 1: read record from 200 - 300;
    int start_order = 200;
    auto to_read = new order[100];
    auto read_records = fdb.read_order(to_read, start_order, 100);
    if (read_records != 100)
    {
        cout << "Cannot read records\n";
        assert(false);
    }
    for (int i = 0; i < 100; i++)
    {
        assert(to_read[i].orderID == 50 + i + start_order);
        assert(to_read[i].amount == 10 + i + start_order);
    }
    delete [] to_read;
    // cleanup
    remove_db_file(file_db_name);
    cout << "[PASSED] " << __func__ << "\n";
}

void test_insert_search_update()
{
    string file_db_name = "test_db_file2.db";
    // Remove stale previous test DB
    remove_db_file(file_db_name);

    file_db fdb(file_db_name);

    for (int i = 0; i < 100; i++)
    {
        order new_order;
        new_order.orderID = 50 + i;
        new_order.amount = i;
        memset(new_order.owner, 'a' + i % 26, sizeof(new_order.owner));
        fdb.insert_order(&new_order);
    }

    for (int i = 99; i >= 0; i--)
    {
        order res;
        int offset = fdb.search_order(50 + i, &res);
        assert(offset == i);
        assert(res.amount == i);
    }

    // Update
    for (int i = 0; i < 100; i++)
    {
        order new_order;
        new_order.orderID = 50 + i;
        new_order.amount = i * 2;
        memset(new_order.owner, 'a' + i % 26, sizeof(new_order.owner));
        assert(fdb.update_order(&new_order) == true);
    }

    for (int i = 0; i < 100; i++)
    {
        order res;
        int offset = fdb.search_order(50 + i, &res);
        assert(offset == i);
        if (res.amount != i * 2)
        {
            cout << res.amount << " vs " << (2 * i) << endl;
            assert(res.amount == 2 * i);
        }
    }
    // cleanup
    remove_db_file(file_db_name);
    cout << "[PASSED] " << __func__ << "\n";
}

int main()
{
    // Run unit tests;
    test_insert_read();
    test_insert_search_update();
    return 0;
}
