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

#include "DetailsThumbnail.hpp"

#include "optionsenums.h"
#include "Settings.hpp"
#include "file/FileInfo.hpp"
#include "metadata/Metadata.hpp"
#include "widgets/ConvertDialog.hpp"

#include <QTreeWidgetItem>
#include <QSvgRenderer>
#include <QGraphicsSvgItem>
#include <QPainter>
#include <QDir>

using namespace sir;


DetailsThumbnail::DetailsThumbnail(Settings *settings)
{
    isSvg = false;

#ifdef SIR_METADATA_SUPPORT
    metadataEnabled = bool(settings->metadata.enabled);
#endif // SIR_METADATA_SUPPORT
}

bool DetailsThumbnail::isRenderedFromSVG() const {
    return isSvg;
}

QSize DetailsThumbnail::size() const {
    return thumbSize;
}

QString DetailsThumbnail::filePath() const {
    return thumbPath;
}

QSize DetailsThumbnail::sourceImageSize() const {
    return imageSize;
}

QString DetailsThumbnail::sourceFilePath() const {
    return imagePath;
}

qint64 DetailsThumbnail::sourceFileSize() const {
    QFileInfo info(imagePath);
    return info.size();
}

#ifdef SIR_METADATA_SUPPORT
bool DetailsThumbnail::isReadFromMetadataThumbnail() const {
    return metadataEnabled;
}

MetadataUtils::ExifStruct *DetailsThumbnail::exifStruct() {
    return &exifStruct_;
}

MetadataUtils::IptcStruct *DetailsThumbnail::iptcStruct() {
    return &iptcStruct_;
}
#endif // SIR_METADATA_SUPPORT

void DetailsThumbnail::writeThumbnail(const FileInfo &fileInfo, int index,
                                      int maxWidth)
{
    QString ext = fileInfo.extension();

    imagePath = fileInfo.fullPath();

    thumbPath = QDir::tempPath() + QDir::separator() + "sir_thumb_"
            + QString::number(index);

    ext = ext.toUpper();

    // thumbnail generation
    if (ext != "SVG" && ext != "SVGZ") {
        bool isThumbSaved = writeThumbnailFromMetadata();
        if (!isThumbSaved)
            writeThumbnailFromImageData(maxWidth);
    }
    else { // render from SVG file
        isSvg = true;
#ifdef SIR_METADATA_SUPPORT
        metadataEnabled = false;
#endif // SIR_METADATA_SUPPORT
        writeThumbnailFromSVG(maxWidth);
    }
}

bool DetailsThumbnail::writeThumbnailFromMetadata() {
#ifdef SIR_METADATA_SUPPORT
    Settings *s = Settings::instance();
    if (s->metadata.enabled) {
        MetadataUtils::Metadata metadata;
        if (metadata.read(imagePath, true)) {
            exifStruct_ = metadata.exifStruct()->copy();
            iptcStruct_ = metadata.iptcStruct()->copy();
            Exiv2::Image::AutoPtr image = metadata.imageAutoPtr();
            imageSize = QSize(image->pixelWidth(), image->pixelHeight());
            Exiv2::PreviewManager previewManager (*image);
            Exiv2::PreviewPropertiesList previewList = previewManager.
                    getPreviewProperties();
            if (previewList.empty())
                return false;
            else { // read from metadata thumnail
                Exiv2::PreviewImage preview = previewManager.getPreviewImage(
                            previewList[0]);
                preview.writeFile(thumbPath.toStdString());
                thumbPath += preview.extension().c_str();
                thumbSize.setWidth(preview.width());
                thumbSize.setHeight(preview.height());
            }
            return true;
        }
        else
            return false;
    }
#endif // SIR_METADATA_SUPPORT

    return false;
}

void DetailsThumbnail::writeThumbnailFromImageData(int maxWidth)
{
    QImage img(imagePath);

    if (!imageSize.isValid())
        imageSize = img.size();
    thumbPath += thumbnailFileExtension;

    QImage thumbnail;
    if (img.width() > maxWidth)
        thumbnail = img.scaledToWidth(maxWidth, Qt::SmoothTransformation);
    else
        thumbnail = img;
    thumbnail.save(thumbPath, thumbnailFileFormat);

    thumbSize = thumbnail.size();
}

void DetailsThumbnail::writeThumbnailFromSVG(int maxWidth)
{
    QGraphicsSvgItem svg(imagePath);
    QSvgRenderer *renderer = svg.renderer();
    QSize size = renderer->defaultSize();
    imageSize = size;

    double sizeRatio = (double) maxWidth / size.width();
    size *= sizeRatio;

    QImage thumbnail (size, QImage::Format_ARGB32);
    thumbnail.fill(Qt::transparent);
    QPainter painter (&thumbnail);
    renderer->render(&painter);

    thumbPath += thumbnailFileExtension;
    thumbnail.save(thumbPath, thumbnailFileFormat);
}
