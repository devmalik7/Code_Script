#!/usr/bin/python3

import csv
import newspaper
import argparse
import json
from datetime import datetime

class WebScraper:
    def __init__(self, url, file_name='news', export_format='json'):
        self.url = url
        
        if export_format not in ['json', 'csv']:
            raise ValueError('Export format must be either json or csv.')
        
        self.export_format = export_format
        
        if export_format == 'json' and not file_name.endswith('.json'):
            self.FILE_NAME = file_name + '.json'
        elif export_format == 'csv' and not file_name.endswith('.csv'):
            self.FILE_NAME = file_name + '.csv'
        else:
            self.FILE_NAME = file_name

    def export_to_JSON(self, articles):
        with open(self.FILE_NAME, 'w') as f:
            articles_dict = [article for article in articles]
            json.dump(articles_dict, f, indent=2)

    def export_to_CSV(self, articles):
        with open(self.FILE_NAME, 'w', newline='') as f:
            writer = csv.DictWriter(f, fieldnames=['title', 'authors', 'publish_date', 'text', 'url'])
            writer.writeheader()
            for article in articles:
                writer.writerow(article)

    def get_one_article(self, url=None):
        target_url = url or self.url
        try:
            article = newspaper.Article(target_url)
            article.download()
            article.parse()
            summary = {
                'title': article.title or "No title found",
                'authors': article.authors or ["Unknown author"],
                'publish_date': article.publish_date.strftime('%Y-%m-%d %H:%M:%S') if article.publish_date else None,
                'text': article.text or "No content found",
                'url': target_url
            }
            return summary
        
        except Exception as e:
            print(f'Error scraping {target_url}: {e}')
            return None

    def get_all_articles(self):
        try:
            summaries = []
            paper = newspaper.build(self.url, memoize_articles=False)
            for art in paper.articles:
                summary = self.get_one_article(art.url)
                if summary:
                    summaries.append(summary)
            return summaries
        
        except Exception as e:
            print(f'Error building newspaper from {self.url}: {e}')
            return []


def main():
    parser = argparse.ArgumentParser(description='Web Scraper for News')
    parser.add_argument('url', help='URL of the webpage to scrape')
    parser.add_argument('--file', '-f', default='news', 
                       help='Custom output file (default: news.json or news.csv)')
    parser.add_argument('--csv-format', '-csv', action='store_true',
                       help='Export to CSV format instead of JSON format')
    parser.add_argument('--all-articles', '-a', action='store_true',
                       help='Get all articles linked to URL instead of only the article from the URL itself')
    
    args = parser.parse_args()
    
    export_format = 'csv' if args.csv_format else 'json'
    
    try:
        web_scraper = WebScraper(
            url=args.url, 
            file_name=args.file, 
            export_format=export_format
        )
        
        if args.all_articles:
            articles = web_scraper.get_all_articles()
        else:
            single_article = web_scraper.get_one_article()
            articles = [single_article] if single_article else []
        
        article_count = len(articles)

        if articles:
            if export_format == 'json':
                web_scraper.export_to_JSON(articles)
            else:
                web_scraper.export_to_CSV(articles)
            
            print(f'Successfully exported {article_count} articles to {web_scraper.FILE_NAME}')
        else:
            print('No articles found to export.')
            
    except Exception as e:
        print(f'Error: {e}')


if __name__ == '__main__':
    main()