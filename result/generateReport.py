from reportlab.lib.pagesizes import letter
from reportlab.platypus import SimpleDocTemplate, Table, TableStyle
from reportlab.lib import colors


# Function to parse JSON files and extract analysis data
def parse_json_for_report(file_path):
    with open(file_path, 'r') as file:
        data = json.load(file)
        return data


# Create a PDF for the report
report_file_path = '/mnt/data/analysis_report.pdf'
pdf = SimpleDocTemplate(report_file_path, pagesize=letter)

# List to hold each part of the report
elements = []

# Parsing and processing each file
for file_path in file_paths:
    data = parse_json_for_report(file_path)
    algorithm = data['Algorithm']
    total_files = data['totalFiles']
    total_time = data['Total Time Taken']

    # Creating the table data
    table_data = [['Name', 'TimeTaken', 'totalWords', 'positiveWords', 'negativeWords', 'polarity', 'stopWords']]
    table_data.extend([[
        item['name'], item['TimeTaken'], item['totalWords'], item['positiveWords'],
        item['negativeWords'], item['polarity'], item['stopWords']] for item in data['analysis']])

    # Adding a page break if not the first table
    if elements:
        from reportlab.platypus import PageBreak

        elements.append(PageBreak())

    # Adding the table with a title
    title = f"{algorithm} - Total Files: {total_files} - Total Time: {total_time} seconds"
    elements.append(Table([[title]], colWidths=[460], style=[('ALIGN', (0, 0), (-1, -1), 'CENTER'),
                                                             ('TEXTCOLOR', (0, 0), (-1, -1), colors.blue),
                                                             ('FONTSIZE', (0, 0), (-1, -1), 14)]))
    table = Table(table_data, colWidths=[70, 70, 70, 70, 70, 70, 70])
    table.setStyle(TableStyle([('INNERGRID', (0, 0), (-1, -1), 0.25, colors.black),
                               ('BOX', (0, 0), (-1, -1), 0.25, colors.black),
                               ('BACKGROUND', (0, 0), (-1, 0), colors.grey)]))
    elements.append(table)

# Build the PDF
pdf.build(elements)

print(f"Report generated: {report_file_path}")
