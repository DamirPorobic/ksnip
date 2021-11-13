/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "X11SnippingArea.h"

X11SnippingArea::X11SnippingArea() : AbstractSnippingArea()
{
	setWindowFlags(windowFlags() | Qt::Tool | Qt::X11BypassWindowManagerHint);

	calculateDesktopGeometry();
}

QRect X11SnippingArea::selectedRectArea() const
{
	if(isBackgroundTransparent()) {
		return mCaptureArea;
	} else {
		return mHdpiScaler.scale(mCaptureArea);
	}
}

void X11SnippingArea::setFullScreen()
{
    setFixedSize(QDesktopWidget().size());
    QWidget::showFullScreen();
}

QRect X11SnippingArea::getSnippingAreaGeometry() const
{
    return mDesktopGeometry;
}

void X11SnippingArea::calculateDesktopGeometry()
{
	auto screens = QApplication::screens();
	for(auto screen : screens) {
		auto scaleFactor = screen->devicePixelRatio();
		auto screenGeometry = screen->geometry();
		int x = screenGeometry.x() / scaleFactor;
		int y = screenGeometry.y() / scaleFactor;
		auto width = screenGeometry.width();
		auto height = screenGeometry.height();

		mDesktopGeometry = mDesktopGeometry.united({x, y, width, height});
	}
}