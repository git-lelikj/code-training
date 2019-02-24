#include <bits/stdc++.h>
#include <boost/signals2/signal.hpp>
#include <boost/algorithm/string.hpp>
using namespace std;

class Text_document
{
public:
    using Text = string;
    using Signal_signature = void(const Text&);
    using Signal_type = boost::signals2::signal<Signal_signature>;
    
    Text_document()
    {}
    
    void append(const string& s)
    {
        text_ += s;
        signal_(text_);
    }
    
    string& text() { return text_; }
    const string& text() const { return text_; }
    
    Signal_type& signal() { return signal_; }
    const Signal_type& signal() const { return signal_; }
    
private:
    string text_;
    Signal_type signal_;
};

class Text_plain_view
{
public:
    Text_plain_view()
    {}
    
    void show(const string& text)
    {
        cout << text;
    }
    
    void register_slot(Text_document& doc)
    {
        doc.signal().connect([this](const string& t){ show(t); });
    }
    
private:
};

class Text_histogram_view
{
public:
    Text_histogram_view()
    {}
    
    void show(const string& text)
    {
        if (!text.size())
            return;
        unordered_map<string, size_t> hist;
        vector<string> words;
        boost::split(words, text, boost::is_any_of(" "));
        for (auto& w: words) {
            auto it = hist.find(w);
            if (it != hist.end()) {
                ++(*it).second;
            }
            else {
                hist.insert({w, 1});
            }
        }
        cout << endl;
        for (auto& e: hist) {
            cout << e.first << ": " << e.second << endl;
        }
    }
    
    void register_slot(Text_document& doc)
    {
        doc.signal().connect([this](const string& t){ show(t); });
    }
    
private:
};


int main()
{
#if 0
    {
        Text_document doc;
        doc.append("excuse me");
        cout << "doc text: " << doc.text() << endl;
        doc.append(", your balls are showing");
        cout << "doc text: " << doc.text() << endl;
    }
#endif
    {
        Text_document doc;
        Text_plain_view plain_view;
        Text_histogram_view hist_view;
        plain_view.register_slot(doc);
        hist_view.register_slot(doc);
        
        doc.append("Due to a language restriction, it is not currently possible to define specializations for stl containers without including the corresponding header. To decrease the overhead needed by this inclusion, user can selectively include a specialization header for a specific container. They are located in boost/algorithm/string/stl directory. Alternatively she can include boost/algorithm/string/std_collection_traits.hpp header which contains specializations for all stl containers.");
        cout << endl;
        doc.append("Try nslookup google.com to determine if there's a DNS issue. 192.168.1.254 is your local network address and it looks like your system is using it as a DNS server. Is this your gateway/modem router as well? What happens when you try ping google.com. Can you browse to it on a Internet web browser?");
        cout << endl;
    }
    
    return 0;
}