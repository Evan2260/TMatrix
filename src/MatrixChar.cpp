/*
 * Copyright (C) 2018-2020 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "MatrixChar.h"
#include "Random.h"
#include "Terminal.h"

int MatrixChar::GetRandomMCharIndex()
{
	return Random::Random(ALL_MCHARS.size());
}

void MatrixChar::SetRandomMChar()
{
	int newIndex {GetRandomMCharIndex()};
	while (MCharIndex == newIndex) {
		newIndex = GetRandomMCharIndex();
	}

	MCharIndex = newIndex;
}

void MatrixChar::Draw() const
{
	terminal->Draw(x, y, ALL_MCHARS[MCharIndex], ColorShade);
}

void MatrixChar::Erase() const
{
	terminal->Erase(x, y);
}

void MatrixChar::Update()
{
	if (UpdateTimer.IsZeroTimer()) {
		return;
	}

	if (UpdateTimer.HasExpired()) {
		UpdateTimer.Reset();
		SetRandomMChar();
		Draw();
	}
	UpdateTimer.Update();
}

void MatrixChar::SetColorShade(int colorShade)
{
	if (colorShade != ColorShade) {
		ColorShade = colorShade;
		Draw();
	}
}
