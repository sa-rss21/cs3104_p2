<!DOCTYPE html>
<html lang="en-GB">
    <head>

        <title>Web Login Service - Loading Session Information</title>

        <meta charset="utf-8">
        <meta http-equiv="X-UA-Compatible" content="IE=EDGE" />
        <link rel="canonical" href="http://www.st-andrews.ac.uk">
        <meta name="copyright" content="Copyright (c) 2021 University of St Andrews" />
        <meta name="rating" content="general" />
        <meta name="dc.keywords" content="University"/>
        <meta name="viewport" content="width=device-width, initial-scale=1.0" />
        <meta name="robots" content="noindex">

        <link href="https://www.st-andrews.ac.uk/~cdn/dpl/1.26.0/styles/screen.css" rel="stylesheet" type="text/css" media="screen" />

        <style>
        .category-header__title{
          font-family: 'PT Serif', georgia, serif;
          color: white;
          font-weight: normal;
          text-decoration: none;
        }
        </style>

        <script>
        <!--
"use strict";
function readLocalStorage(key) {
    var success;
    try {
        var value = localStorage.getItem(key);
        if (value != null) {
            document.form1["shib_idp_ls_value." + key].value = value;
        }
        success = "true";
    } catch (e) {
        success = "false";
        document.form1["shib_idp_ls_exception." + key].value = e;
    }
    document.form1["shib_idp_ls_success." + key].value = success;
}

function isLocalStorageSupported() {
    try {
        localStorage.setItem("shib_idp_ls_test", "shib_idp_ls_test");
        localStorage.removeItem("shib_idp_ls_test");
        return true;
    } catch (e) {
        return false;
    }
}
        // -->
        </script>
    </head>
    <body onload="doLoad()">

        <!-- Begin pattern: header //-->
        <nav class="sr-only" aria-label="Accessibility links"><a href="#content-begin">Skip to content</a></nav>
        <header id="header" class="">
            <div class="row" >
                <div id="logo-container">
                    <div id="header-logo"><a href="https://www.st-andrews.ac.uk/"><span>University of St Andrews</span></a></div>
                </div>
            </div>
        </header>

        <nav id="category-header" aria-label="Category header">
        <div class="container">
            <div class="category-header__title">Single sign-on</div>
        </div>
        </nav>

        <!-- End pattern: header //-->
        <main id="content-begin">
             <div class="container">
                <div class="row">
                    <div class="col-xs-12 content">

                    <h1>Web Login Service - Loading Session Information</h1>

                    Loading login session information from the browser...

                    <noscript>
                        Since your browser does not support JavaScript, you must press the Continue button once to proceed.
                    </noscript>
<form name="form1" action="/idp/profile/cas/login?execution=e1s1" method="post">
    <input type="hidden" name="csrf_token" value="_61f12282e4ba44b725afd3df9c9905501c26920c" />
        <input name="shib_idp_ls_exception.shib_idp_session_ss" type="hidden" />
        <input name="shib_idp_ls_success.shib_idp_session_ss" type="hidden" value="false" />
        <input name="shib_idp_ls_value.shib_idp_session_ss" type="hidden" />
        <input name="shib_idp_ls_exception.shib_idp_persistent_ss" type="hidden" />
        <input name="shib_idp_ls_success.shib_idp_persistent_ss" type="hidden" value="false" />
        <input name="shib_idp_ls_value.shib_idp_persistent_ss" type="hidden" />
    <input name="shib_idp_ls_supported" type="hidden" />
    <input name="_eventId_proceed" type="hidden" />
    <noscript>
        <input type="submit" value="Continue" />
    </noscript>
</form>

<script>
<!--
function doLoad() {
    var localStorageSupported = isLocalStorageSupported();
    document.form1["shib_idp_ls_supported"].value = localStorageSupported;
    if (localStorageSupported) {
        readLocalStorage("shib_idp_session_ss");
        readLocalStorage("shib_idp_persistent_ss");
    }
    document.form1.submit();
}
// -->
</script>
                  </div>
                </div>
              </div>
          </main>

<footer id="footer">
  <div id="university-footer">
    <div class="container">
      <div class="row">
        <div class="col-lg-8">
          <p id="footer-charity" role="contentinfo">© 2021 The University of St&nbsp;Andrews is a charity registered in Scotland, No: SC013532</p>
          <ul id="footer-links">
<li><a class="footer-links__link cookie-control__open" aria-controls="ccc-module" tabindex="0">Cookie preferences</a></li>
            <li><a href="https://www.st-andrews.ac.uk/digital-standards/accessibility/accessibility-statement/"  class="footer-links__link">Accessibility statement</a></li>
            <li><a href="https://www.st-andrews.ac.uk/terms/"  class="footer-links__link">Terms and conditions</a></li>
            <li><a href="https://www.st-andrews.ac.uk/help/" class="footer-links__link">Website help</a></li>
          </ul>
        </div>
        
        <div class="col-lg-4">
          <ul id="social">
             <li><a href="https://www.facebook.com/uniofsta"  class="footer-links__link"><span class="sr-only">Facebook</span><i class="fa fa-facebook-square fa-2x" title="Facebook"></i></a></li>
             <li><a href="https://twitter.com/univofstandrews/"  class="footer-links__link"><span class="sr-only">Twitter</span><i class="fa fa-twitter-square fa-2x" title="Twitter"></i></a></li>
             <li><a href="https://www.instagram.com/uniofstandrews"  class="footer-links__link"><span class="sr-only">Instagram</span><i class="fa fa-instagram fa-2x" title="Instagram"></i></a></li>
             <li><a href="https://www.youtube.com/uofstandrews"  class="footer-links__link"><span class="sr-only">YouTube</span><i class="fa fa-youtube-square fa-2x" title="YouTube"></i></a></li>
          </ul>
        </div>
      </div>
    </div>
  </div>
</footer>
    </body>
</html>
