QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AppContext.cpp \
    AppInitializer.cpp \
    AppView.cpp \
    ConvertableToBytes.cpp \
    Error.cpp \
    FileManager.cpp \
    FormData.cpp \
    FormTemplate.cpp \
    FormWidget.cpp \
    MainCore.cpp \
    MainCoreWorker.cpp \
    NetworkCore.cpp \
    NetworkRequestCreator.cpp \
    NetworkRequestExecutor.cpp \
    NetworkResponsePreparer.cpp \
    NetworkResponsePreparerBase.cpp \
    NetworkResponsePreparerRSS.cpp \
    NetworkSourceContextPreparer.cpp \
    News.cpp \
    NewsParserBase.cpp \
    NewsParserStandardRSS.cpp \
    NewsParserTelegram.cpp \
    NewsParserVK.cpp \
    ParserDictionary.cpp \
    PreparableObject.cpp \
    RawNewsDataBase.cpp \
    SourceBase.cpp \
    SourceContextInterface.cpp \
    SourceContextTelegram.cpp \
    SourceContextVK.cpp \
    SourceDictionary.cpp \
    SourceListModel.cpp \
    SourceListModelRSS.cpp \
    SourceListModelTelegram.cpp \
    SourceListWidget.cpp \
    SourceStandardRSS.cpp \
    SourceTelegram.cpp \
    SourceVK.cpp \
    SourcesFileManager.cpp \
    StringDictionary.cpp \
    StringDictionaryItem.cpp \
    TextKeyWordsExtractor.cpp \
    TextKeyWordsExtractorContext.cpp \
    ThreadedQueue.cpp \
    ThreadedStringDictionary.cpp \
    ThreadedTransactionData.cpp \
    main.cpp

HEADERS += \
    AppContext.h \
    AppInitializer.h \
    AppView.h \
    ConvertableToBytes.h \
    Error.h \
    FileManager.h \
    FormData.h \
    FormTemplate.h \
    FormWidget.h \
    MainCore.h \
    MainCoreWorker.h \
    NetworkCore.h \
    NetworkRequestCreator.h \
    NetworkRequestExecutor.h \
    NetworkResponsePreparer.h \
    NetworkResponsePreparerBase.h \
    NetworkResponsePreparerRSS.h \
    NetworkSourceContextPreparer.h \
    News.h \
    NewsParserBase.h \
    NewsParserStandardRSS.h \
    NewsParserTelegram.h \
    NewsParserVK.h \
    ParserDictionary.h \
    PreparableObject.h \
    RawNewsDataBase.h \
    SourceBase.h \
    SourceContextInterface.h \
    SourceContextTelegram.h \
    SourceContextVK.h \
    SourceDictionary.h \
    SourceListModel.h \
    SourceListModelRSS.h \
    SourceListModelTelegram.h \
    SourceListWidget.h \
    SourceStandardRSS.h \
    SourceTelegram.h \
    SourceVK.h \
    SourcesFileManager.h \
    StringDictionary.h \
    StringDictionaryItem.h \
    TextKeyWordsExtractor.h \
    TextKeyWordsExtractorContext.h \
    ThreadedQueue.h \
    ThreadedStringDictionary.h \
    ThreadedTransactionData.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libs/QGumboParser/QGumboParser/release/ -lQGumboParser
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libs/QGumboParser/QGumboParser/debug/ -lQGumboParser
else:unix: LIBS += -L$$OUT_PWD/../libs/QGumboParser/QGumboParser/ -lQGumboParser

INCLUDEPATH += $$PWD/../libs/QGumboParser/QGumboParser
DEPENDPATH += $$PWD/../libs/QGumboParser/QGumboParser

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/QGumboParser/QGumboParser/release/libQGumboParser.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/QGumboParser/QGumboParser/debug/libQGumboParser.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/QGumboParser/QGumboParser/release/QGumboParser.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libs/QGumboParser/QGumboParser/debug/QGumboParser.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libs/QGumboParser/QGumboParser/libQGumboParser.a
