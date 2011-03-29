/*
* This file is part of SIR, an open-source cross-platform Image tool
* 2007  Rafael Sachetto
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
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
* Contact e-mail: Rafael Sachetto <rsachetto@gmail.com>
* Program URL: http://sir.projet-libre.org/
*
*/

#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include "ui_optionsdialog.h"


class QSettings;
class QDir;
class QImageWriter;
class ConvertDialog;
class LanguageUtils;

using namespace std;

class OptionsDialog : public QDialog, public Ui::OptionsDialog {
    Q_OBJECT

public:
    OptionsDialog( QWidget * parent = 0, Qt::WFlags f = 0);
    ~OptionsDialog();
	int getOption();	
    void createLanguageMenu();
    void createConnections();
    bool checkDcrawPath(QString fileName);
    LanguageUtils * languages;
    QMap<QString, QString> * fileToNiceName;
    
private slots:
    virtual void writeSettings();
	virtual void readSettings();
    virtual void browseDestination();
    virtual void browseDcraw();
    virtual void setRawStatus(int state);

signals:
    void ok();

};
#endif
