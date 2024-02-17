// TinyAudioLink - Seamlessly transfer Audio between USB capable devices
// Copyright (C) 2019 Michael Fabian 'Xaymar' Dirks
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once
#include <cinttypes>
#include <cstddef>

// This is critical, so ensure it's byte aligned.
#pragma pack(push, 1)

extern std::size_t __stackStart;

namespace nvic {
	typedef void (*interrupt_function_t)();

	struct interruptVectorTable_t {
		std::size_t*         initialStackPointer = &__stackStart;
		interrupt_function_t reset               = 0;
		interrupt_function_t interrupts[240]     = {0};
	};
} // namespace nvic

#pragma pack(pop)
