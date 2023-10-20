'''
MIT License

Copyright (c) 2023 limitless Aeronautics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

'''

from bs4 import BeautifulSoup
from pathlib import Path
import base64

# Read the original HTML
original_html_text = Path('index.html').read_text(encoding="utf-8")
soup = BeautifulSoup(original_html_text, 'html.parser')

# Lists to store CSS and JavaScript content
css_content = []
js_content = []

# Find link tags (CSS)
for tag in soup.find_all('link', rel='stylesheet'):
    if tag.has_attr('href'):
        file_text = Path(tag['href']).read_text(encoding="utf-8")
        css_content.append(file_text)
        tag.extract()

# Find script tags (JavaScript)
for tag in soup.find_all('script', src=True):
    if tag.has_attr('src'):
        file_text = Path(tag['src']).read_text()
        js_content.append(file_text)
        tag.extract()

# Insert merged CSS content
if css_content:
    style_tag = soup.new_tag('style')
    style_tag.string = '\n'.join(css_content)
    soup.head.append(style_tag)

# Insert merged JavaScript content
if js_content:
    script_tag = soup.new_tag('script')
    script_tag.string = '\n'.join(js_content)
    soup.body.append(script_tag)

# Create the 'dist' directory if it doesn't exist
Path("dist").mkdir(parents=True, exist_ok=True)

# Save the merged HTML file
with open("dist/oneindex.html", "w", encoding="utf-8") as outfile:
    outfile.write(str(soup))
    
print('Done')