# Web Scraper

A Python command-line tool for scraping news articles from websites using the `newspaper3k` library. The tool can extract individual articles or all articles from a news website and export them to JSON or CSV format.

## Features

- **Single Article Scraping**: Extract content from a specific article URL
- **Bulk Article Scraping**: Scrape all articles linked from a news website homepage
- **Multiple Export Formats**: Export data as JSON or CSV
- **Custom File Names**: Specify custom output file names
- **Article Metadata**: Extract title, authors, publication date, content, and URL

## Installation

1. Ensure you have Python 3.6+ installed
2. Install the required dependencies:

```bash
pip install newspaper3k
```

## Usage

### Basic Single Article Scraping

```bash
python web_scraper.py "https://example.com/news-article"
```

This will create a `news.json` file with the scraped article data.

### Scrape All Articles from a News Site

```bash
python web_scraper.py "https://example-news.com" --all-articles
```

### Export to CSV Format

```bash
python web_scraper.py "https://example.com/article" --csv-format
```

### Custom Output File Name

```bash
python web_scraper.py "https://example.com/article" --file my_articles
```

### Combine Options

```bash
# Scrape all articles and export as CSV with custom filename
python web_scraper.py "https://example-news.com" -a -csv -f my_data
```

## Command Line Arguments

| Argument | Short | Description | Default |
|----------|-------|-------------|---------|
| `url` | - | URL of the webpage to scrape (required) | - |
| `--file` | `-f` | Custom output filename | `news` |
| `--csv-format` | `-csv` | Export to CSV instead of JSON | `False` |
| `--all-articles` | `-a` | Scrape all articles from the site | `False` |

## Output Format

### JSON Output
```json
[
  {
    "title": "Article Title",
    "authors": ["Author One", "Author Two"],
    "publish_date": "2023-10-15 14:30:00",
    "text": "Full article content...",
    "url": "https://example.com/article"
  }
]
```

### CSV Output
The CSV file will contain columns for:
- `title`
- `authors` (as a string representation of the list)
- `publish_date`
- `text`
- `url`

## Examples

1. **Scrape a single article to JSON:**
   ```bash
   python web_scraper.py "https://www.bbc.com/news/world-us-canada-12345678"
   ```

2. **Scrape all articles from CNN and export as CSV:**
   ```bash
   python web_scraper.py "https://www.cnn.com" -a -csv -f cnn_articles
   ```

3. **Scrape with custom JSON filename:**
   ```bash
   python web_scraper.py "https://example.com/article" -f my_article_data
   ```

## Notes

- The tool uses the `newspaper3k` library which may not work with all websites, especially those with heavy JavaScript rendering or anti-scraping measures
- Some news sites may block automated scraping attempts
- The quality of extracted content depends on the website's structure and the `newspaper3k` library's parsing capabilities
- For sites with many articles, using `--all-articles` may take considerable time

## Error Handling

- If scraping fails, the tool will display an error message
- Empty results will be indicated with appropriate messages
- Network issues and parsing errors are caught and reported

## License

This tool is provided for educational and personal use. Please respect website terms of service and robots.txt files when scraping.