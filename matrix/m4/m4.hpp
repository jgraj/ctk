struct m4f {
	f32 data[16];

	constexpr m4f() = default;
	constexpr m4f(f32 _00, f32 _01, f32 _02, f32 _03, f32 _10, f32 _11, f32 _12, f32 _13, f32 _20, f32 _21, f32 _22, f32 _23, f32 _30, f32 _31, f32 _32, f32 _33);

	constexpr f32& operator[] (size_t index);
	constexpr const f32& operator[] (size_t index) const;
	m4f transposed() const;

	static m4f mul(m4f a, m4f b);
	static constexpr m4f ident();
};