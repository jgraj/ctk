struct m3f {
	f32 data[9];

	constexpr m3f() = default;
	constexpr m3f(f32 _00, f32 _01, f32 _02, f32 _10, f32 _11, f32 _12, f32 _20, f32 _21, f32 _22);

	constexpr f32& operator[] (size_t index);
	constexpr const f32& operator[] (size_t index) const;
	m3f transposed() const;

	static constexpr m3f ident();
};