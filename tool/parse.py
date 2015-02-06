import sys
import glob
import xml.etree.ElementTree as ET

participant_dir = "../in/PGP-participant/"

for profile_file in glob.glob(participant_dir+"*.xml"):
    tree = ET.parse(profile_file)
    root = tree.getroot()

# tree = ET.parse('hu1904EC.xml')
# root = tree.getroot()

# for arg in sys.argv:
#     print arg

#for child in root.findall(".//*[@class='admin_table']/{http://www.w3.org/1999/xhtml}tr/{http://www.w3.org/1999/xhtml}td"):
#print child.get
#print child.attrib

#for info in root.iter('h3'):
    for info in root.iter('{http://www.w3.org/1999/xhtml}table'):
        if info.get('class') == "admin_table":
            for td in info.find('{http://www.w3.org/1999/xhtml}tr'):
                print td.text

    # retrive title
    for tt in root.iter('{http://www.w3.org/1999/xhtml}title'):
        print tt.text
