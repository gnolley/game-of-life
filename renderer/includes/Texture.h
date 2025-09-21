#pragma once

namespace GoL
{

	class Texture
	{
	public:
		Texture() = default;
		Texture(unsigned int width, unsigned int height);

		void bind() const;
		void clear() const;

	private:
		unsigned int id {};
		unsigned int width{}, height{};
	};

}