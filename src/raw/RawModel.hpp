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

#ifndef RAWMODEL_HPP
#define RAWMODEL_HPP

#include <QString>

class Settings;


class RawModel
{
public:
    enum RawTab
    {
        BasicTab,
        AdvancedTab
    };

    RawModel();
    RawModel(bool enabled, const QString &dcrawPath, const QString &dcrawOptions);
    RawModel(const RawModel &other);
    ~RawModel();

    void swap(const RawModel &other);

    bool isValid() const;

    void load(const Settings &settings);
    void save(Settings *settings);

    bool isEnabled() const;
    void setEnabled(bool value);
    QString dcrawPath() const;
    void setDcrawPath(const QString &value);
    QString dcrawOptions() const;
    void setDcrawOptions(const QString &value);
    RawTab rawTab() const;
    void setRawTab(RawTab value);

private:
    bool enabled;
    QString dcrawPathString;
    QString dcrawOptionsString;
    RawTab tab;
};

#endif // RAWMODEL_HPP
