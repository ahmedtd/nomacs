/*******************************************************************************************************
 DkSettings.h
 Created on:	07.07.2011
 
 nomacs is a fast and small image viewer with the capability of synchronizing multiple instances
 
 Copyright (C) 2011-2013 Markus Diem <markus@nomacs.org>
 Copyright (C) 2011-2013 Stefan Fiel <stefan@nomacs.org>
 Copyright (C) 2011-2013 Florian Kleber <florian@nomacs.org>

 This file is part of nomacs.

 nomacs is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 nomacs is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 *******************************************************************************************************/

#pragma once

#pragma warning(push, 0)	// no warnings from includes - begin
#include <QSettings>
#include <QBitArray>
#include <QColor>
#include <QDate>
#include <QSharedPointer>
#pragma warning(pop)	// no warnings from includes - end

#pragma warning(disable: 4251)	// TODO: remove

#ifndef DllCoreExport
#ifdef DK_CORE_DLL_EXPORT
#define DllCoreExport Q_DECL_EXPORT
#elif DK_DLL_IMPORT
#define DllCoreExport Q_DECL_IMPORT
#else
#define DllCoreExport Q_DECL_IMPORT
#endif
#endif

class QFileInfo;
class QTranslator;

namespace nmc {

class DkWhiteListViewModel;

class DllCoreExport DkFileFilterHandling {

public:
	DkFileFilterHandling() {};
	void registerNomacs(bool showDefaultApps = false);
	void registerFileType(const QString& filterString, const QString& attribute, bool add);
	void showDefaultSoftware() const;

protected:
	QString registerProgID(const QString& ext, const QString& friendlyName, bool add);
	void registerExtension(const QString& ext, const QString& progKey, bool add);
	void setAsDefaultApp(const QString& ext, const QString& progKey, bool defaultApp);
	void registerDefaultApp(const QString& ext, const QString& progKey, bool defaultApp);
	QString getIconID(const QString& ext) const;

	QStringList getExtensions(const QString& filter) const;
	QStringList getExtensions(const QString& filter, QString& friendlyName) const;
};

class DllCoreExport DkSettings {

public:
	DkSettings();

	enum modes {
		mode_default = 0,
		mode_frameless,
		mode_contrast,
		mode_default_fullscreen,
		mode_frameless_fullscreen,
		mode_contrast_fullscreen,
		mode_end,
	};

	enum sortMode {
		sort_filename,
		sort_date_created,
		sort_date_modified,
		sort_random,
		sort_end,
	};

	enum sortDir {
		sort_ascending,
		sort_descending,

		sort_dir_end,
	};

	enum rawThumb {
		raw_thumb_always,
		raw_thumb_if_large,
		raw_thumb_never,

		raw_thumb_end,
	};

	enum keepZoom {
		zoom_always_keep,
		zoom_keep_same_size,
		zoom_never_keep,

		zoom_end,
	};

	enum syncModes {
		sync_mode_default = 0,
		sync_mode_remote_display,
		sync_mode_remote_control,
		sync_mode_receiveing_command,

		sync_mode_end,
	};

	enum TransitionMode {
		trans_appear,
		trans_fade,
		trans_swipe,

		trans_end
	};

	struct App {
		bool showToolBar;
		bool showMenuBar;
		bool showStatusBar;
		bool showMovieToolBar;
		QBitArray showFilePreview;
		QBitArray showFileInfoLabel;
		QBitArray showPlayer;
		QBitArray showMetaData;
		QBitArray showHistogram;
		QBitArray showOverview;
		QBitArray showScroller;
		QBitArray showComment;
		QBitArray showExplorer;
		QBitArray showMetaDataDock;
		QBitArray showEditDock;
		QBitArray showHistoryDock;
		bool showRecentFiles;
		bool useLogFile;
		int appMode;
		int currentAppMode;
		bool privateMode;
		bool advancedSettings;
		bool closeOnEsc;
		bool maximizedMode;
		QStringList browseFilters;
		QStringList registerFilters;

		QStringList fileFilters;	// just the filters
		QStringList openFilters;	// for open dialog
		QStringList saveFilters;	// for save dialog
		QStringList rawFilters;
		QStringList containerFilters;
		QString containerRawFilters;
	};

	struct Display {
		int keepZoom;
		bool zoomToFit;
		bool invertZoom;
		bool tpPattern;
		QColor highlightColor;
		QColor hudBgColor;
		QColor bgColor;
		QColor bgColorFrameless;
		QColor hudFgdColor;
		QColor iconColor;
		bool defaultBackgroundColor;
		bool defaultIconColor;
		int thumbSize;
		int iconSize;
		int thumbPreviewSize;
		//bool saveThumb;
		int interpolateZoomLevel;
		bool showCrop;
		bool antiAliasing;
		bool toolbarGradient;	// 05.01.2016 - deprecated
		bool showBorder;
		bool displaySquaredThumbs;
		bool showThumbLabel;
		
		TransitionMode transition;
		bool alwaysAnimate;
		float animationDuration;
	};

	struct Global {
		int skipImgs;
		int numFiles;
		bool loop;
		bool scanSubFolders;

		QString lastDir;
		QString lastSaveDir;
		QStringList recentFiles;
		QStringList recentFolders;
		bool logRecentFiles;
		bool checkOpenDuplicates;
		bool extendedTabs;
		bool useTmpPath;
		bool askToSaveDeletedFiles;
		QString tmpPath;
		QString language;
		QStringList searchHistory;
		
		Qt::KeyboardModifier altMod;
		Qt::KeyboardModifier ctrlMod;
		bool zoomOnWheel;
		bool horZoomSkips;
		bool doubleClickForFullscreen;
		bool showBgImage;

		QString setupPath;
		QString setupVersion;
		int numThreads;

		int sortMode;
		int sortDir;
		QString pluginsDir;
	};

	struct SlideShow {
		int filter;
		float time;
		bool silentFullscreen;
		QBitArray display;
		QColor backgroundColor;
		float moveSpeed;
	};
	struct Sync {
		bool enableNetworkSync;
		bool allowTransformation;
		bool allowPosition;
		bool allowFile;
		bool allowImage;
		bool checkForUpdates;
		bool updateDialogShown;
		QDate lastUpdateCheck;
		bool syncAbsoluteTransform;
		bool switchModifier;
		QStringList recentSyncNames;
		QStringList syncWhiteList;
		QHash<QString, QVariant> recentLastSeen;
		int syncMode;
		bool syncActions;
	};
	struct MetaData {
		bool ignoreExifOrientation;
		bool saveExifOrientation;
	};
		
	struct Resources {
		float cacheMemory;
		float historyMemory;
		int maxImagesCached;
		bool waitForLastImg;
		bool filterRawImages;
		bool filterDuplicats;
		int loadRawThumb;
		QString preferredExtension;
		int numThumbsLoading;
		int maxThumbsLoading;
		bool gammaCorrection;
	};

	//enums for checkboxes - divide in camera data and description
	enum cameraData {
		camData_size,
		camData_orientation,
		camData_make,
		camData_model,
		camData_aperture,
		camData_iso,
		camData_flash,
		camData_focal_length,
		camData_exposure_mode,
		camData_exposure_time,

		camData_end
	};

	enum DisplayItems{
		display_file_name,
		display_creation_date,
		display_file_rating,

		display_end
	};

	QStringList translatedCamData() const;
	QStringList translatedDescriptionData() const;

	void initFileFilters();
	void loadTranslation(const QString& fileName, QTranslator& translator);
	QStringList getTranslationDirs();

	void load(QSettings& settings, bool defaults = false);
	void save(QSettings& settings, bool force = false);
	void setToDefaultSettings();
	void setNumThreads(int numThreads);

	bool isPortable();
	QString settingsPath() const;

	double dPIScaleFactor(QWidget *w = 0) const;
	int effectiveIconSize(QWidget *w = 0) const;
	int effectiveThumbSize(QWidget *w = 0) const;
	int effectiveThumbPreviewSize(QWidget *w = 0) const;

	App& app();
	Global& global();
	Display& display();
	SlideShow& slideShow();
	Sync& sync();
	MetaData& metaData();
	Resources& resources();

protected:
	QStringList scamDataDesc;
	QStringList sdescriptionDesc;

	App app_p;
	Global global_p;
	Display display_p;
	SlideShow slideShow_p;
	Sync sync_p;
	MetaData meta_p;
	Resources resources_p;

	App app_d;
	Global global_d;
	Display display_d;
	SlideShow slideShow_d;
	Sync sync_d;
	MetaData meta_d;
	Resources resources_d;

	void init();
};

class DllCoreExport DkSettingsManager {

public:
	static DkSettingsManager& instance();
	~DkSettingsManager();

	// singleton
	DkSettingsManager(DkSettingsManager const&)		= delete;
	void operator=(DkSettingsManager const&)		= delete;


	static DkSettings& param();		// convenience
	QSettings& qSettings();
	DkSettings& settings();			// rename
	void init();

	static void importSettings(const QString& settingsPath);

private:
	DkSettingsManager();

	QSettings* mSettings = 0;
	DkSettings* mParams = 0;
};

};
