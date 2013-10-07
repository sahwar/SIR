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

#include "sharedinformation.h"
#include "settings.h"
#include "metadatautils.h"

/** Default constructor.\n
  * Sets default field values.
  */
SharedInformation::SharedInformation() {
    // synchronization threads settings
    overwriteAll = false;
    noOverwriteAll = false;
    overwriteResult = 1;
    abort = false;
    enlargeAll = false;
    noEnlargeAll = false;
    enlargeResult = 1;
    // image settings
    width = 0;
    height = 0;
    hasWidth = false;
    hasHeight = false;
    maintainAspect = true;
    sizeBytes = 0;
    sizeUnit = 0;
    quality = 100;
    rotate = false;
    angle = 0.;
#ifdef SIR_METADATA_SUPPORT
    // metadata settings
    saveMetadata = true;
    realRotate = false;
    updateThumbnail = true;
    rotateThumbnail = false;
#endif // SIR_METADATA_SUPPORT
}

/** Set desired size in pixels or percent, depend on \a percent value.
  * \param width Width of desired image.
  * \param height Height of desired image.
  * \param percent Sets desired width and height in pixels if false, otherwise
  *     sets size as percent of original image size.
  * \param hasWidth Sets desired width to \a width if true.
  * \param hasHeight Sets desired height to \a height if true.
  * \param maintainAspect If true image will be scaled with keeping apsect ratio.
  */
void SharedInformation::setDesiredSize(int width, int height, bool percent,
                                       bool widthSet, bool heightSet,
                                       bool keepAspect) {
    this->width = width;
    this->height = height;
    this->hasWidth = widthSet;
    this->hasHeight = heightSet;
    this->maintainAspect = keepAspect;
    if (percent)
        sizeUnit = 1;
    else
        sizeUnit = 0;
}

/** Sets disired size in bytes. Result file size can be lower
  * but never grower than \a bytes.
  * \par
  * This is overloaded function.
  */
void SharedInformation::setDesiredSize(quint32 bytes) {
    sizeBytes = bytes;
    sizeUnit = 2;
}

/** Sets desired format string without point prefix.
  * \note Call this function after calling #setSaveMetadata.
  */
void SharedInformation::setDesiredFormat(const QString &format) {
    this->format = format;
#ifdef SIR_METADATA_SUPPORT
    if (!MetadataUtils::Metadata::isWriteSupportedFormat(format)) {
        saveMetadata = false;
        realRotate = true;
        qWarning("Format \"%s\" haven't write metadata support",
                 format.toLatin1().constData());
    }
    else
        saveMetadata = Settings::instance()->metadata.saveMetadata;
#endif // SIR_METADATA_SUPPORT
}

/** Allows rotate and set desired rotation angle.
  * \param rotate Allows rotate.
  * \param angle Clockwise rotation angle.
  */
void SharedInformation::setDesiredRotation(bool rotate, double angle) {
    this->rotate = rotate;
    int multipler = angle / 360;
    this->angle = angle - multipler*360;
}

/** Sets desired flip mode.
  * \param flip Index of flip combo box. Supported values:
  * \li 0 <c>None flip</c>
  * \li 1 <c>Flip verticaly</c>
  * \li 2 <c>Flip horizontaly</c>
  * \li 3 <c>Flip verticaly and horizontaly</c>
  * \sa MetadataUtils::Flip
  */
void SharedInformation::setDesiredFlip(int flip) {
    this->flip = flip;
}

/** Sets desired image quality.
  * \param quality Integer factor in range 0 to 100.
  */
void SharedInformation::setQuality(int quality) {
    this->quality = quality;
}

/** Sets destination file name prefix. */
void SharedInformation::setDestPrefix(const QString& destPrefix) {
    this->prefix = destPrefix;
}

/** Sets destination file name suffix. */
void SharedInformation::setDestSuffix(const QString &destSuffix) {
    this->suffix = destSuffix;
}

/** Sets destination directory path. */
void SharedInformation::setDestFolder(const QDir& destFolder) {
    this->destFolder = destFolder;
}

/** Allows overwrite all files. */
void SharedInformation::setOverwriteAll(bool overwriteAll) {
    this->overwriteAll = overwriteAll;
}

#ifdef SIR_METADATA_SUPPORT
/** Enables (or disables) metadata support if true, otherwise disables metadata
  * support.
  * \sa setSaveMetadata()
  */
void SharedInformation::setMetadataEnabled(bool value) {
    this->metadataEnabled = value;
}

/** Enables (or disables) save metadata option if true, otherwise disables
  * saving metadata.
  * \note Call this function before calling #setDesiredFormat.
  * \sa setMetadataEnabled()
  */
void SharedInformation::setSaveMetadata(bool value) {
    this->saveMetadata = value;
}

/** Enables (or disables) real rotation for converted images.
  * \note If metadata disabled image converting thread always do real rotate.
  * \sa setMetadataEnabled()
  */
void SharedInformation::setRealRotate(bool rotate) {
    this->realRotate = rotate;
}

/** Enables (or disables) thumbnail update for converted images. */
void SharedInformation::setUpdateThumbnail(bool update) {
    this->updateThumbnail = update;
}

/** Enables (or disables) thumbnail rotation for converted images. */
void SharedInformation::setRotateThumbnail(bool rotate) {
    this->rotateThumbnail = rotate;
}
#endif // SIR_METADATA_SUPPORT
