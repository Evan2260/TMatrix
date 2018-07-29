/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "Rain.h"
#include "RainStreak.h"
#include "Terminal.h"

void RainStreak::Update()
{
	// Delete the tail MChar
	if (y >= Length) {
		if (!MChars.empty()) {
			MChars.pop_front();
		} else {
			OutOfScreen = true;
		}
	}
	// Remove glow from the previous MChar
	if (!MChars.empty()) {
		MChars.back().SetNotGlowing();
	}
	// Create a new MChar
	if (y < Terminal::getNumberOfRows()) {
		auto [updateRate, updateTime] { rain->GetRandomUpdateRateAndTime() };

		MChars.emplace_back(x, y, updateRate, updateTime);
		MChars.back().Draw();
	}
	// Advance position
	y++;
	// Check if the tail MChar has entered the screen
	if (y >= Length) {
		FullyEnteredScreen = true;
	}
	// Update all the MChars
	if (!OutOfScreen) {
		for (MatrixChar &mc : MChars) {
			mc.Update();
		}
	}
}
