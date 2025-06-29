# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import sys
import subprocess
# sys.path.insert(0, os.path.abspath('.'))


# -- Project information -----------------------------------------------------


# These are defaults set to use with read-the-docs but when generated
# automatically with CMake they will be set using CMake Variables

project = "TanukiGB"
copyright = '2024, James Calo'
author = 'James Calo'

# The full version, including alpha/beta/rc tags
release = "0.0.1"


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [ "breathe"
]

#--------------------------------------------------------------------#
# These are hardcoded values for breathe used so that read-the-docs
# can operate corectly despite not having CMake.
# Therefore, when the documentation is generated automatically with 
# CMake these variables will be set from within CMake using the 
# Sphinx target 
#--------------------------------------------------------------------#
#read-the-docs_doxygen = 
# breathe_projects = { project : "../build/xml/" }
# breathe_default_project = project

breathe_projects = { "TanukiGB" : "../docs_build/xml" }
breathe_default_project = "TanukiGB"
breathe_show_include = True
#breathe_default_members = ('members', 'undoc-members')

breathe_domain_by_extension = {
    "h"   : "cpp",
      "ixx" : "cpp",
      
    }

breathe_domain_by_file_pattern = {
    
    }

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# Theme options
html_theme_options = {
    # If we have a html_logo below, this shows only the logo with no title text
    "logo_only": True,
    # Collapse navigation (False makes it tree-like)
    "collapse_navigation": False,
}


# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

#Relative to html_static_path
html_css_files = [
    "css/style.css","css/colours.css","css/defaults.css","css/dark.css","css/light.css",
]

#if not on_rtd:
#    html_css_files.append("css/dev.css")

html_js_files = [
    
]


#html_logo =  #"img/<ICON_IMAGE>.svg"

######################################################################
## Read the docs config ##
######################################################################

def run_doxygen_on_rtd(path):
  doxygen_command = f"cd {path}; doxygen doxygen/Doxyfile"
  completed_process = subprocess.run(doxygen_command, shell=True,
                                     capture_output=True)
  ret = completed_process.returncode
  if ret != 0:
    doxygen_err_msg = f"*** Doxygen execution failed with return code {ret} ***"
    sys.stderr.write(doxygen_err_msg + "\n")
    sys.stderr.write(completed_process.stderr.decode())
    sys.stderr.write("*****************************\n")
    completed_process.check_returncode()

def generate_doxygen_xml_on_rtd(app):
  # Not -1000 as True is a string here
  if os.environ.get('READTHEDOCS', None) == 'True':
    #Could come up with a cooler and CMakey config method :D
    run_doxygen_on_rtd("..")

def setup(app):
  app.connect("builder-inited", generate_doxygen_xml_on_rtd)
