
#pragma once
#include "../../../utt/icase.hpp"
#include "../../../utt/utt_assert.hpp"
#include "../../../formation/concurrent/slimqless.hpp"
#include "../../../utils/strutils.hpp"
#include "../../../app_info/trace.hpp"
#include <string>
#include <functional>
#include <type_traits>

class slimqless_single_test : public icase
{
private:
    template <typename T>
    static void clear(const T& x) { }
    
    template <typename T>
    static void clear(T* x) { delete x; }

    template <typename T>
    static const T& value(const T& i) { return i; }

    template <typename T>
    static const T& value(const T* i) { return *i; }

    template <typename T>
    bool run_case(const std::function<T(int)>& from_int)
    {
        const int MAX = 10000;
        slimqless<T> q;
        for(int i = 0; i < MAX; i++)
            q.push(from_int(i));
        for(int i = 0; i < MAX; i++)
        {
            T j;
            utt_assert.is_false(q.empty());
            utt_assert.is_true(q.pop(j));
            T i2 = from_int(i);
            utt_assert.equal(value<typename std::remove_pointer<T>::type>(i2),
                             value<typename std::remove_pointer<T>::type>(j),
                             ", ",
                             value<typename std::remove_pointer<T>::type>(i2),
                             ", ",
                             value<typename std::remove_pointer<T>::type>(j));
            clear<typename std::remove_pointer<T>::type>(j);
            clear<typename std::remove_pointer<T>::type>(i2);
            utt_assert.equal(q.empty(), i == MAX - 1);
        }
        return true;
    }

    bool int_case()
    {
        return run_case<int>(
                        [](int i)
                        {
                            return i;
                        });
    }

    bool string_case()
    {
        // boost::lockfree::queue requires trivial destructor and trivial assign
        return run_case<std::string*>(
                        [](int i)
                        {
                            return new std::string(strcat(i));
                        });
        /*
        return run_case<std::string>(
                        [](int i)
                        {
                            return strcat(i);
                        });
        */
    }

public:
    bool run() override
    {
        return int_case() &&
               string_case();
    }

    DEFINE_CASE(slimqless_single_test);
};

REGISTER_CASE(slimqless_single_test);

