QT       += core gui network

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
    SourceListWidget.cpp \
    SourceStandardRSS.cpp \
    SourceTelegram.cpp \
    SourceVK.cpp \
    SourcesFileManager.cpp \
    TextKeyWordsExtractor.cpp \
    ThreadedQueue.cpp \
    ThreadedStringDictionary.cpp \
    ThreadedStringDictionaryItem.cpp \
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
    SourceListWidget.h \
    SourceStandardRSS.h \
    SourceTelegram.h \
    SourceVK.h \
    SourcesFileManager.h \
    TextKeyWordsExtractor.h \
    ThreadedQueue.h \
    ThreadedStringDictionary.h \
    ThreadedStringDictionaryItem.h \
    ThreadedTransactionData.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
