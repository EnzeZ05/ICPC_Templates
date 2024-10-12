using ull = unsigned long long;
using ui = unsigned int;

mt19937_64 rng {
    std::chrono::steady_clock::now().time_since_epoch().count()
};