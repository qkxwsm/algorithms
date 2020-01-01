mt19937 rng(42);

template<class T>
T randomize(T mod)
{
	return uniform_int_distribution<T>(0, mod - 1)(rng);
}
