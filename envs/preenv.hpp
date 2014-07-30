
#pragma once
#include "envs.hpp"
#include "../template/singleton.hpp"
#include <vector>
#include <string>
#include <initializer_list>
#include <boost/algorithm/string.hpp>
#include "../utils/strutils.hpp"

const static class preenv_t
{
public:
    const bool busy_wait;
private:
    static void add_combination(std::vector<std::string>& r, const std::vector<std::string>& inputs)
    {
        using namespace boost::algorithm;
        r.push_back(join(inputs, ""));
        r.push_back(join(inputs, "-"));
        r.push_back(join(inputs, "_"));
    }

    static std::vector<std::string> env_keys(const std::initializer_list<const char*>& segs)
    {
        std::vector<std::string> r;
        std::vector<std::string> inputs(segs.begin(), segs.end());
        add_combination(r, inputs);
        to_upper(inputs);
        add_combination(r, inputs);
        to_lower(inputs);
        add_combination(r, inputs);
        to_initial_upper(inputs);
        add_combination(r, inputs);
        return r;
    }

    preenv_t() :
        busy_wait(envs.has(env_keys({"busy", "wait"})))
    {}

    CONST_SINGLETON(preenv_t);
}& preenv = preenv_t::instance();
