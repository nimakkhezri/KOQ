#include "TriviaAPI.h"

size_t write_data(void* ptr, size_t size, size_t nmemb, void* userdata) {
    ((std::string*)userdata)->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

TriviaAPI::TriviaAPI() {
    this->base_url = "https://opentdb.com/api.php?amount=5&category=";
    this->download_categories();
}

void TriviaAPI::download_categories() {
    CURL* curl = curl_easy_init();

    if (curl) {
        std::string responce;
        std::string url = "https://opentdb.com/api_category.php";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responce);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            nlohmann::json data = nlohmann::json::parse(responce);

            const auto& results = data["trivia_categories"];
            for (const auto& category : results) {
                QString category_name = QString::fromStdString(category["name"]);
                int category_id = category["id"];
                categories.push_back(Category(category_name, category_id));
            }
        }

        curl_easy_cleanup(curl);
    }

}

Category TriviaAPI::category_identifier(QString name){
    for (const Category& category : categories){
        if (category.get_name() == name)
            return category;
    }
    return Category("Any", 0);
}


void TriviaAPI::get_questions(const Category& category, const QString& difficulty){
    std::ofstream file("questions.json");

    CURL* curl = curl_easy_init();
    if (curl) {
        std::string responce;
        std::string url = base_url + std::to_string(category.get_id()) + "&difficulty=" + difficulty.toStdString() + "&type=multiple";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responce);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            nlohmann::json data = nlohmann::json::parse(responce);

            if (file.is_open()) {
                file << data.dump(4);
                file.close();
            }else{
                qDebug() << "questions.json can't write ... ";
            }
        }

        curl_easy_cleanup(curl);
    }
}
