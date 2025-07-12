<?php
assert_options(ASSERT_BAIL, 1);
assert(!get_magic_quotes_gpc());

require( 'library/sql.php' );

///////////////////////////////////////////////////////////////////////////////
//
// Library Code
//
///////////////////////////////////////////////////////////////////////////////

function Index_PageStyles()
{
?>
<style>

body
{
	padding:0;
	margin:0;
	border:0;
	background:#555;
	min-width:1150px;
}

div#wrapper
{
	margin:1em;
	padding:0;
	width:auto;
	background: white;
	vertical-align:top;
}

div#topbar
{
	margin:0;
	padding:0;
	background:white;
	border:2px solid gray;
}

#topbar a:link , #topbar a:visited , #topbar a:hover , #topbar a:active
{
	display: inline-block;
	margin:0;
	padding:0;
	width: 150px;
	border: 1px solid darkgray;
	text-align:center;
	color:black;
	background-color:lightgray;
	text-decoration:none;
	font-weight:bold;
}

#topbar a:hover
{
	background-color:black;
	color:white;
}

#header
{
	margin:0;
	padding:0;
	border:2px solid black;
	background-color:black;
	color:white;
	text-align:center;
}

#google_search
{
	margin:0;
	background-color:white;
	text-align:center;
	padding:2em 1em 2em 1em;
	border:0px solid green;
}

#columns_wrapper
{
	margin:0;
	padding:0;
	border:0px solid orange;
	margin-left:auto;
	margin-right:auto;
	text-align:center;
	background-color:black;
	width:100%;
}

div.column
{
	width:30%;
	margin:0;
	padding:.5em;
	border:0;
	display: inline-block;
	vertical-align:top;
	background-color:black;
	color:white;
	width: 350px;
}

div.widget
{
	width:100%;
	border:1px solid darkblue;
	vertical-align:top;
	background-color:white;
	color:black;
	text-align:left;
}

div.widget:hover
{
	background-color:white;
}

div.links
{

}

.links a
{
	color:#000;
	text-decoration:none;
}

.links a:hover
{
	font-weight:bold;
	text-decoration:underline;
}

.links ul
{
	margin:0;
	border:0;
	padding:1em;
}

.links li
{
	font-size:10pt;
	list-style-type:none;
	border:0px solid black;
}

.widget h2
{
	text-align:center;
	font-weight:bold;
	padding:0;
	margin:0;
	border:0;
	font-size:14pt;
	width:100%;
	background-color:darkblue;
	color:white;
}

</style>
<?php
}

function Index_PageStart()
{
	print( "<!DOCTYPE html>\n" );
	print( "<html>\n" );
	print( "<head>\n" );
	print( "<title>Jack's Really Cool Home Page</title>\n" );
	Index_PageStyles();
	print( "</head>\n" );
	print( "<body>\n" );
	print( "<div id=\"wrapper\">" );
}

function Index_PageEnd()
{
	print( "</div>" );
	?>
	<script>
	window.onload = function() 
	{
		document.getElementById("GoogleSearchBox").focus();
	};
	</script>
	<?php
	print( "</body>\n" );
	print( "</html>\n" );
}

function Index_BeginColumn()
{
	print( "<div class=\"column\">" );
}

function Index_EndColumn()
{
	print( "</div>" );
}

function Index_BeginWidget()
{
	print( "<div class=\"widget\">" );
}

function Index_EndWidget()
{
	print( "</div>" );
}

function Index_ShowGoogleSearch()
{
?>
<div id="google_search">
<center>
<form method="get" action="http://www.google.com/search">
<div style="border:2px solid black;padding:4px;width:30em;">
<table border="0" align="center" cellpadding="0">
<tr><td>
<input type="text"   name="q" size="50" style="color:#808080;" id="GoogleSearchBox"
maxlength="255" value="Google Search"
onfocus="if(this.value==this.defaultValue)this.value=''; this.style.color='black';" onblur="if(this.value=='')this.value=this.defaultValue; "/>
<input type="submit" value="Google Search" />
</table>
</div>
</form>
</center>
</div>
<?php
}

function Index_ShowWeather()
{
	Index_BeginWidget();
	?>
	<h2>Weather</h2>
	<br/>
	
<a href="http://www.accuweather.com/en/us/little-elm-tx/75068/weather-forecast/2103611" class="aw-widget-legal">
<!--
By accessing and/or using this code snippet, you agree to AccuWeather’s terms and conditions (in English) which can be found at http://www.accuweather.com/en/free-weather-widgets/terms and AccuWeather’s Privacy Statement (in English) which can be found at http://www.accuweather.com/en/privacy.
-->
</a><div id="awcc1466289822756" class="aw-widget-current"  data-locationkey="2103611" data-unit="f" data-language="en-us" data-useip="false" data-uid="awcc1466289822756"></div><script type="text/javascript" src="http://oap.accuweather.com/launch.js"></script>
	
<a href="http://www.accuweather.com/en/us/frisco-tx/75033/weather-forecast/346100" class="aw-widget-legal">
<!--
By accessing and/or using this code snippet, you agree to AccuWeather’s terms and conditions (in English) which can be found at http://www.accuweather.com/en/free-weather-widgets/terms and AccuWeather’s Privacy Statement (in English) which can be found at http://www.accuweather.com/en/privacy.
-->
</a><div id="awcc1466289780817" class="aw-widget-current"  data-locationkey="346100" data-unit="f" data-language="en-us" data-useip="false" data-uid="awcc1466289780817"></div><script type="text/javascript" src="http://oap.accuweather.com/launch.js"></script>

<a href="http://www.accuweather.com/en/us/little-elm-tx/75068/current-weather/2103611" class="aw-widget-legal">
<!--
By accessing and/or using this code snippet, you agree to AccuWeather’s terms and conditions (in English) which can be found at http://www.accuweather.com/en/free-weather-widgets/terms and AccuWeather’s Privacy Statement (in English) which can be found at http://www.accuweather.com/en/privacy.
-->
</a><div id="awtd1466289460879" class="aw-widget-36hour"  data-locationkey="" data-unit="f" data-language="en-us" data-useip="true" data-uid="awtd1466289460879" data-editlocation="true"></div><script type="text/javascript" src="http://oap.accuweather.com/launch.js"></script>

	<?php
	Index_EndWidget();
}

function Index_ShowNews()
{
	Index_BeginWidget();
	?>
	<h2>News</h2>
	<center>
	<script src="http://nmp.newsgator.com/NGBuzz/buzz.ashx?buzzId=81519&apiToken=C9A08C5818F54101B19714C0283D5F70&trkP=&trkM=4CF440BA-6F09-219C-A09E-05DE4370F05E" type="text/javascript"></script>
	</center>
	<center>
	<script src="//www.gmodules.com/ig/ifr?url=http://igwidgets.com/lig/gw/f/islk/89/slkm/ik/s/1329844/87/charles447/google-news.xml&amp;up_subject=Google%20News&amp;up_entries=3&amp;up_summaries=100&amp;up_selectedTab=&amp;synd=open&amp;w=290&amp;h=390&amp;title=Google+News&amp;border=%23ffffff%7C1px%2C1px+solid+black%7C1px%2C1px+solid+black%7C0px%2C1px+black&amp;output=js"></script>
	</center>
	<?php
	Index_EndWidget();
}

function Index_ShowWidgetLinks()
{
	global $WidgetLinks;
	Index_BeginWidget();
	print( "<h2>Quick Links</h2>" );
	print( "<div class=\"links\">" );
	print( "<ul>\n" );
	for( $i = 0; $i < count( $WidgetLinks ); $i++ )
	{
		printf( "<li><a href=\"%s\">%s</a></li>\n", $WidgetLinks[$i]['txtUrl'], $WidgetLinks[$i]['txtDesc'] );
	}
	print( "</ul>\n" );
	print( "</div>" );
	Index_EndWidget();
}

function Index_DrawColumns()
{
	print( "<div id=\"columns_wrapper\">" );

	Index_BeginColumn();
	Index_ShowWidgetLinks();
	Index_EndColumn();

	Index_BeginColumn();
	Index_ShowWeather();
	Index_EndColumn();

	Index_BeginColumn();
	Index_ShowNews();
	Index_EndColumn();

	printf( "</div>" );
}

function Index_DrawHeader()
{
	print( "<div id=\"header\">" );
	print( "<h1>Jack's Really Cool Home Page</h1>" );
	print( "</div>" );
}

function Index_DrawTopBar()
{
	global $TopLinks;
	
	print( "<div id=\"topbar\">" );
	for( $i = 0; $i < count( $TopLinks ); $i++ )
	{
		printf( "<a href=\"%s\">%s</a>", $TopLinks[$i]['txtUrl'], $TopLinks[$i]['txtDesc'] );
	}
	print( "</div>" );
}

///////////////////////////////////////////////////////////////////////////////
//
// Entry Point
//
///////////////////////////////////////////////////////////////////////////////

Sql_Init();

$TopLinks    = Sql_DoSelectQuery( 'home_tblLinks' , '*' , 'txtType="TOPBAR"', 'txtDesc' );
$WidgetLinks = Sql_DoSelectQuery( 'home_tblLinks' , '*' , 'txtType="WIDGET"', 'txtDesc' );

Index_PageStart();
Index_DrawTopBar();
Index_DrawHeader();
Index_ShowGoogleSearch();
Index_DrawColumns();
Index_PageEnd();

Sql_Deinit();

?>
