/* This file is part of SIR, an open-source cross-platform Image tool
 * 2007-2010  Rafael Sachetto <rsachetto@gmail.com>
 * 2011-2016  Marek Jędryka   <jedryka89@gmail.com>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Program URL: http://marek629.github.io/SIR/
 */

#ifndef VERSIONTEST_H
#define VERSIONTEST_H

#include <QtTest/QTest>
#include "Version.hpp"

#undef VERSION
#define VERSION "2.3"

class VersionTest : public QObject {
    Q_OBJECT

public:
    VersionTest();

private:
    Version ver;

private slots:
    void initTestCase();
    void version();
    void vector_data();
    void vector();
    void isAtLeast_data();
    void isAtLeast();
};

Q_DECLARE_METATYPE( QVector<int> )

#endif // VERSIONTEST_H
