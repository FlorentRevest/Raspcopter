# Taki kiepski hack na Bartkom po to by sie skompilowala statyczna bibloteka
# najpierw - prawdopodobnie z czasem bedzie dodawana jako dynamiczna bibloteka 
#

TEMPLATE    = subdirs
CONFIG     += ordered 
SUBDIRS     = analogwidgets \
              scripttool \
	      test 

OTHER_FILES += \
    android/src/eu/licentia/necessitas/ministro/IMinistroCallback.aidl \
    android/src/eu/licentia/necessitas/ministro/IMinistro.aidl \
    android/src/eu/licentia/necessitas/industrius/QtApplication.java \
    android/src/eu/licentia/necessitas/industrius/QtSurface.java \
    android/src/eu/licentia/necessitas/industrius/QtLayout.java \
    android/src/eu/licentia/necessitas/industrius/QtActivity.java \
    android/src/eu/licentia/necessitas/mobile/QtFeedback.java \
    android/src/eu/licentia/necessitas/mobile/QtMediaPlayer.java \
    android/src/eu/licentia/necessitas/mobile/QtSensors.java \
    android/src/eu/licentia/necessitas/mobile/QtAndroidContacts.java \
    android/src/eu/licentia/necessitas/mobile/QtCamera.java \
    android/src/eu/licentia/necessitas/mobile/QtLocation.java \
    android/src/eu/licentia/necessitas/mobile/QtSystemInfo.java \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-mdpi/icon.png \
    android/AndroidManifest.xml \
    android/src/eu/licentia/necessitas/ministro/IMinistroCallback.aidl \
    android/src/eu/licentia/necessitas/ministro/IMinistro.aidl \
    android/src/eu/licentia/necessitas/industrius/QtApplication.java \
    android/src/eu/licentia/necessitas/industrius/QtSurface.java \
    android/src/eu/licentia/necessitas/industrius/QtLayout.java \
    android/src/eu/licentia/necessitas/industrius/QtActivity.java \
    android/src/eu/licentia/necessitas/mobile/QtFeedback.java \
    android/src/eu/licentia/necessitas/mobile/QtMediaPlayer.java \
    android/src/eu/licentia/necessitas/mobile/QtSensors.java \
    android/src/eu/licentia/necessitas/mobile/QtAndroidContacts.java \
    android/src/eu/licentia/necessitas/mobile/QtCamera.java \
    android/src/eu/licentia/necessitas/mobile/QtLocation.java \
    android/src/eu/licentia/necessitas/mobile/QtSystemInfo.java \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-mdpi/icon.png \
    android/AndroidManifest.xml \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/origo/QtApplication.java \
    android/src/org/kde/necessitas/origo/QtActivity.java \
    android/version.xml \
    android/res/values-et/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-id/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-ja/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-ms/strings.xml
