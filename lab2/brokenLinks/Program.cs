using System;
using System.Collections.Generic;
using System.IO;
using System.Net.Http;
using System.Text;
using HtmlAgilityPack;

namespace brokenLinks
{
    class Program
    {
        private readonly string _mainUrl = "http://91.210.252.240/broken-links/";
        private HttpClient _httpClient = new HttpClient();
        private List<string> _allLinks = new List<string>();
        private StreamWriter _validUrl = new StreamWriter("../../../valid.txt", false, Encoding.UTF8);
        private StreamWriter _invalidUrl = new StreamWriter("../../../invalid.txt", false, Encoding.UTF8);
        private int _validCounter = 0;
        private int _invalidCounter = 0;
        private bool IsValid(HttpResponseMessage response)
        {
            return response.StatusCode.GetHashCode() < 300 && response.StatusCode.GetHashCode() > 199;
        }

        private void PrintToInvalidOutput(string message)
        {
            _invalidUrl.WriteLine(message);
        }

        private void PrintToValidOutput(string message)
        {
            _validUrl.WriteLine(message);
        }

        private void EmplaceLinks(HttpResponseMessage response)
        {
            string htmlCode = response.Content.ReadAsStringAsync().Result;
            var htmlDocument = new HtmlDocument();
            htmlDocument.LoadHtml(htmlCode);
            var links = htmlDocument.DocumentNode.SelectNodes("//a");
            foreach (var link in links)
            {
                string srcLink = link.GetAttributeValue("href", null);
                if (srcLink != null & srcLink != "#" & !_allLinks.Contains(srcLink))
                {
                    _allLinks.Add(srcLink);
                }
            }
        }

        public void GetAllLinksFromPage(string url)
        {
            using (var response = _httpClient.GetAsync(url).Result)
            {
                string message = $"{url} {response.StatusCode.GetHashCode()} {response.ReasonPhrase}";
                if (IsValid(response))
                {
                    EmplaceLinks(response);
                }
                else
                {
                    PrintToInvalidOutput(message);
                    _invalidCounter++;
                }
            }
        }

        private void PrintInfoAndCloseFiles()
        {
            PrintToValidOutput($"\nValid links count: {_validCounter}\nCheck date : {DateTime.UtcNow} UTC");
            PrintToInvalidOutput($"Invalid links count: {_invalidCounter}\nCheck date : {DateTime.UtcNow} UTC");
            _validUrl.Close();
            _invalidUrl.Close();
        }

        private string FormCorrectLink(string link)
        {
            return (link != "https://colorlib.com") ? _mainUrl + link : link;

        }

        public void CheckAllLinks()
        {
            foreach (string link in _allLinks)
            {
                Console.WriteLine(link);
                using (var response = _httpClient.GetAsync(FormCorrectLink(link)).Result)
                {
                    string message = $"{FormCorrectLink(link)} {response.StatusCode.GetHashCode()} {response.ReasonPhrase}";
                    if (IsValid(response))
                    {
                        PrintToValidOutput(message);
                        _validCounter++;
                    }
                    else
                    {
                        PrintToInvalidOutput(message);
                        _invalidCounter++;
                    }
                }
            }
            PrintInfoAndCloseFiles();
        }
        static void Main(string[] args)
        {
            Program myProgram = new Program();
            string[] mainLinks = new string[]
            {
                "http://91.210.252.240/broken-links/",
                "http://91.210.252.240/broken-links/index.html",
                "http://91.210.252.240/broken-links/about.html",
                "http://91.210.252.240/broken-links/work.html",
                "http://91.210.252.240/broken-links/pricing.html",
                "http://91.210.252.240/broken-links/blog.html",
                "http://91.210.252.240/broken-links/contact.html"
            };
            foreach (string link in mainLinks)
            {
                myProgram.GetAllLinksFromPage(link);
            }
            myProgram.CheckAllLinks();
        }
    }
}
