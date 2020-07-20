/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
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

#include "HdpiScaler.h"

QRect HdpiScaler::unscale(const QRect &rect) const
{
	auto factor = scaleFactor();
	return {
		static_cast<int>(rect.x() / factor),
		static_cast<int>(rect.y() / factor),
		static_cast<int>(rect.width() / factor),
		static_cast<int>(rect.height() / factor)
	};
}

QRect HdpiScaler::scale(const QRect &rect) const
{
	auto factor = scaleFactor();
	return {
		static_cast<int>(rect.x() * factor),
		static_cast<int>(rect.y() * factor),
		static_cast<int>(rect.width() * factor),
		static_cast<int>(rect.height() * factor)
	};
}

qreal HdpiScaler::scaleFactor() const
{
	auto desktopWidget = QApplication::desktop();
	
#if defined(__APPLE__)
	qDebug("devicePixelRatio: %s", qPrintable(QString::number(desktopWidget->devicePixelRatio())));
	qDebug("devicePixelRatioF: %s", qPrintable(QString::number(desktopWidget->devicePixelRatioF())));
	qDebug("logicalDpiX: %s", qPrintable(QString::number(desktopWidget->logicalDpiX())));
	qDebug("logicalDpiY: %s", qPrintable(QString::number(desktopWidget->logicalDpiY())));
	qDebug("physicalDpiX: %s", qPrintable(QString::number(desktopWidget->physicalDpiX())));
	qDebug("physicalDpiY: %s", qPrintable(QString::number(desktopWidget->physicalDpiY())));
	
	auto scaleFactor = static_cast<qreal>(desktopWidget->physicalDpiX()) / static_cast<qreal>(desktopWidget->logicalDpiX());
	qDebug("ScaleFacotr: %s", qPrintable(QString::number(scaleFactor)));
	return scaleFactor;
#endif
	
#if defined(__linux__) || defined(_WIN32)
	return desktopWidget->devicePixelRatioF();
#endif
}
