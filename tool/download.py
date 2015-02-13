######################################################
# download participants' survey file form PGP website
######################################################

import sys
import urllib2
import xml.etree.ElementTree as ET

# configurations
pgp_url = "https://my.pgp-hms.org/"
pgp_overview_html = "public_genetic_data"
# https://my.pgp-hms.org/public_genetic_data main html
pgp_main = "mypgp"

profile_dir = "./profiles/"

# get the overview data page from which we extract participants' general
# infomation such as id, time, genome file, profile file, 

# WARNING: before we use this overview html file
# we'd better to convert it to xml format otherwise element tree
# module would fail

#response = urllib2.urlopen(pgp_url+pgp_overview_html)
#html = open(pgp_main, 'w')
#html.write(response.read())
#html.close()

tree = ET.parse(pgp_main+".xml")
root = tree.getroot()
root_tag = root.tag.strip("html")

for tr in root.iter(root_tag+'tr'):
    if tr.get('data-participant-id') != '': # find each participant becuase each has id
        #print tr.get('data-participant-id')
        for td in tr.iter(root_tag+'td'):
            # get participant id
            p_id = ""
            if td.get('data-summarize-as') == "participant":
                p_id = td.find(root_tag+'a').text
                p_url = pgp_url+td.find(root_tag+'a').get('href')
                print "Downloading " + p_url
                #remote_profile = urllib2.urlopen(p_url)
                #profile = open(profile_dir+p_id+".html", 'w')
                #profile.write(remote_profile.read())
                #profile.close()
            # time & data name
            elif td.get('data-summarize-as') == "list-distinct":
                print td.text
            # data type
            elif td.get('data-summarize-as') == "name":
                print td.text
            # data download url
            elif td.get('data-summarize-as') == "size":
                print "To Download"
            # report download url
            elif td.get('data-summarize-as') == "none":
                a = td.find(root_tag+'a')
                if a is not None: 
                  print a.get('href')
    print "---------------------------------------------\n"
