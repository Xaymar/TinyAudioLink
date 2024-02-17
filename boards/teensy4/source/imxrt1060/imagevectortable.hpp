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
#include "imxrt1060/bootdata.hpp"

#ifndef USE_TEENSY_IVT
#include "imxrt1060/nvic.hpp"
#endif

// This is critical, so ensure it's byte aligned.
#pragma pack(push, 1)

namespace imxrt1060 {
#ifndef USE_TEENSY_IVT
	/** Image Vector Table 4.0/4.1
	 * - Mentioned here https://forum.pjrc.com/index.php?threads/teensy-4-imagevectortable-not-matching-the-nxp-format.67562/#post-282356
	 * - Unclear where that user got the information from, since I could not find this documentation they are talking about.
	 */
	struct image_vector_table_t {
		// 0x00 Big Endian Header: Tag, Length, Version in one field.
		uint32_t header = 0x412000D1;
		// 0x04 Entry: Absolute address of the first instruction?
		::imxrt1060::nvic::interrupt_vector_table_t* ivt = &::imxrt1060::nvic::__interrupt_vector_table;
		// 0x08 Reserved, must be zero.
		uint32_t __reserved1 = 0;
		// 0x0C Device Configuration Data: Absolute address but optional, so it's NULL.
		void* dcd = nullptr;
		// 0x10 Boot Data: Absolute address of the boot data.
		boot_data_t* bootData = nullptr;
		// 0x14 Image Vector Table: The address of this structure.
		image_vector_table_t* self = nullptr;
		// 0x18 Command Sequence File: See High-Assurance Boot for details. Must be NULL if not performing HAB.
		void* csf = nullptr;
		// 0x1C Reserved, must be zero.
		uint32_t __reserved2 = 0;
	}; // 0x20
	static constexpr std::size_t image_vector_table_sz = 0x20;
	static_assert(sizeof(image_vector_table_t) == image_vector_table_sz, "Image Vector Table must be 32 bytes long.");
#else
	/** Image Vector Table 4.3
	 * - IMXRT1060RM_rev3.pdf: Chapter 9, Program image, Image and Vector Table and Boot Data
	 * - IMXRT1060RM_rev1_Processor_Manual.pdf: 8.7.1
	 */
	struct image_vector_table_t {
		// 0x00 Big Endian Header: Tag, Length, Version in one field.
		uint32_t header = 0x432000D1; // Teensy 4.x ships with a different version (4.3) that jumps straight to code.
		// 0x04 Entry: Absolute address of the first instruction?
		void (*entryPoint)() = nullptr;
		// 0x08 Reserved, must be zero.
		uint32_t __reserved1 = 0;
		// 0x0C Device Configuration Data: Absolute address but optional, so it's NULL.
		void* dcd = nullptr;
		// 0x10 Boot Data: Absolute address of the boot data.
		boot_data_t* bootData = nullptr;
		// 0x14 Image Vector Table: The address of this structure.
		image_vector_table_t* self = nullptr;
		// 0x18 Command Sequence File: See High-Assurance Boot for details. Must be NULL if not performing HAB.
		void* csf = nullptr;
		// 0x1C Reserved, must be zero.
		uint32_t __reserved2 = 0;
	}; // 0x20
	static constexpr std::size_t image_vector_table_sz = 0x20;
	static_assert(sizeof(image_vector_table_t) == image_vector_table_sz, "Image Vector Table must be 32 bytes long.");
#endif

	extern image_vector_table_t __image_vector_table;
} // namespace imxrt1060

#pragma pack(pop)
