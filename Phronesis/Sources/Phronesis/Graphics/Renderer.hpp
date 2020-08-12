#pragma once

#include <memory>

#include "Phronesis/Core/Module.hpp"

namespace Phronesis
{
	class RendererImpl
	{
	public:
		virtual ~RendererImpl() = default;
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void dispose() = 0;
		virtual void requestResize() = 0;
	};

	class Renderer : public Module
	{
	public:
		Renderer();

		void init();
		void update() override;
		void dispose() override;

		void requestResize();

		RendererImpl* getImpl() const;

	private:
		std::unique_ptr<RendererImpl> impl;
	};
}
