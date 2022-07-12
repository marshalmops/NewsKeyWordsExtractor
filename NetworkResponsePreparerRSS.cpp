#include "NetworkResponsePreparerRSS.h"

namespace {

bool getFirstWrappedStringAndCutOut(const QString &leftWrapper,
                                    const QString &rightWrapper,
                                    QString &content,
                                    QString &wrappedContent)
{
    if (leftWrapper.isEmpty() || rightWrapper.isEmpty() || content.isEmpty())
        return false;
    
    auto leftWrapperLength  = leftWrapper.length();
    auto rightWrapperLength = rightWrapper.length();
    
    if ((leftWrapperLength + rightWrapperLength) >= content.length()) return false;
    
    auto leftWrapperIndex  = content.indexOf(leftWrapper);
    auto rightWrapperIndex = content.indexOf(rightWrapper);
    
    if (leftWrapperIndex <= -1 || rightWrapperIndex <= -1 || leftWrapperIndex >= rightWrapperIndex)
        return false;
    
    QString wrappedContextBuffer{content.mid(leftWrapperIndex + leftWrapperLength,
                                             rightWrapperIndex - leftWrapperIndex - rightWrapperLength + 1)};
    
    if (wrappedContextBuffer.isEmpty()) return false;
    
    wrappedContent = std::move(wrappedContextBuffer);
    
    content = content.mid(rightWrapperIndex + rightWrapperLength);
    
    return true;
};

}

NetworkResponsePreparerRSS::NetworkResponsePreparerRSS(const std::shared_ptr<NetworkRequestExecutor> &executor)
    : NetworkResponsePreparerBase{executor}
{
    
}

bool NetworkResponsePreparerRSS::prepareResponse(const QByteArray &responseBytes, 
                                                 std::vector<QByteArray> &preparedData)
{
    if (responseBytes.isEmpty()) return false;
    
    // getting links from provided XML...
    
    QString rawNewsString{QString::fromUtf8(responseBytes)};
    std::vector<QUrl> newsLinks{};
    
    while (true) {
        QString curItemContent{};
        
        if (!getFirstWrappedStringAndCutOut("<item>", "</item>", rawNewsString, curItemContent))
            break;
        
        QString curLinkString{};
        
        if (!getFirstWrappedStringAndCutOut(C_LINK_TAG_OPENING, C_LINK_TAG_ENDING, curItemContent, curLinkString))
            break;
        
        QUrl linkUrl{curLinkString};
        
        if (!linkUrl.isValid()) return false;
        
        newsLinks.push_back(std::move(linkUrl));
    }
    
    if (newsLinks.empty()) return false;
    
    // getting news pages by gotten links...
    
    std::vector<QByteArray> preparedDataBuffer{};
    
    foreach (const auto &link, newsLinks) {
        QNetworkRequest newRequest{link};
        QByteArray curResponse{};
        
        if (!m_executor->executeGetRequest(newRequest, curResponse))
            return false;
        
        //responseBytesBuffer += curResponse;
        preparedDataBuffer.push_back(curResponse);
    }
    
    preparedData = std::move(preparedDataBuffer);
    
    return true;
}
