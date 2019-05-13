/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef MATRIX_CHAR_H
#define MATRIX_CHAR_H

#include <array>
#include <cstring>
#include "Active.h"
#include "CountdownTimer.h"

class MatrixChar : public Active {
	static constexpr std::array ALL_MCHARS {
		"ﾊ", "ﾐ", "ﾋ", "ｰ", "ｳ", "ｼ", "ﾅ", "ﾓ", "ﾆ", "ｻ",
		"ﾜ", "ﾂ", "ｵ", "ﾘ", "ｱ", "ﾎ", "ﾃ", "ﾏ", "ｹ", "ﾒ",
		"ｴ", "ｶ", "ｷ", "ﾑ", "ﾕ", "ﾗ", "ｾ", "ﾈ", "ｽ", "ﾀ",
		"ﾇ", "ﾍ", "𐌇", "0", "1", "2", "3", "4", "5", "7",
		"8", "9", "Z", ":", ".", "･", "=", "*", "+", "-",
		"<", ">", "¦", "|", "╌", " ", "\""
	};

	const int x;
	const int y;
	CountdownTimer UpdateTimer;
	int MCharIndex {GetRandomMCharIndex()};
	bool Glowing {true};

	static int GetRandomMCharIndex();
	void SetRandomMChar();
	void Draw() const;
	void Erase() const;
public:
	MatrixChar(int X, int Y, int UpdateRate, int UpdateTime) : x{X}, y{Y},
		UpdateTimer{UpdateRate, UpdateTime} {
		Draw();
	}
	~MatrixChar() {
		Erase();
	}

	void Update();
	void SetNotGlowing();

	static constexpr std::size_t GetMaxMCharSize()
	{
		std::size_t longest {0};
		for (const auto &MChar : ALL_MCHARS) {
			std::size_t current {std::strlen(MChar)};
			if (current > longest) {
				longest = current;
			}
		}
		return longest;
	}
};

#endif
