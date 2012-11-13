/*
 * This file is part of SIR, an open-source cross-platform Image tool
 * 2007-2010  Rafael Sachetto
 * 2011-2012  Marek Jędryka
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
 * Contact e-mail: Rafael Sachetto <rsachetto@gmail.com>
 *                 Marek Jędryka   <jedryka89@gmail.com>
 * Program URL: http://sir.projet-libre.org/
 *
 */

#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include "languageutils.h"

/** Default constructor.\n
  * Reads informations about languages and loads into languageInfoMap language
  * information map.
  * \sa LanguageInfo readLanguages()
  */
LanguageUtils::LanguageUtils() {
    this->readLanguages();
}

/** Deallocates memory. */
LanguageUtils::~LanguageUtils() {
    delete languageInfoMap;
}

/** Reads translation info file and creates languageInfoMap language information
  * map.
  * \sa languageInfoMap
  */
void LanguageUtils::readLanguages() {

    /*
        Here we read and create a map to hold the informations about
        Language names
    */

    languageInfoMap = new QMap<QString, LanguageInfo>;

    QFile translationsFile(QCoreApplication::applicationDirPath() +
                           "/../share/sir/translations/translation_info.csv");

    if (!translationsFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&translationsFile);

    while (!in.atEnd()) {

        QString line = in.readLine();

        /*Each line has the format:
          translation_file,Language Name,flag file
        */
        QStringList languageData = line.split(",");

        LanguageInfo info;
        info.niceName = languageData[1];
        info.flagFile = languageData[2];

        languageInfoMap->insert(languageData[0], info);

    }
}

/** Returns LanguageInfo about typed \a language name. */
const LanguageInfo LanguageUtils::getLanguageInfo(const QString & language) const {
    return languageInfoMap->value(language);
}
