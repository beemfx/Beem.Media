<?php

$SiteTitle = 'Beem Media Fun Archives';

$Sites = array 
(
	array ( 'name' => 'Beem Software 1' , 'link' => 'beemsoft1/index.htm' , 'desc' => 'Original Beem Media website, full of bogus information.' ),
	array ( 'name' => 'Beem Software 2' , 'link' => 'beemsoft2/index.html' , 'desc' => 'Another Beem Media website with bogus information.' ),
	array ( 'name' => 'Chainsaw Death' , 'link' => 'flashmovies/cdeath/cdeath.html' , 'desc' => 'A flash movie made while in high school.' ),
	array ( 'name' => 'Guillotine Death' , 'link' => 'flashmovies/gdeath/gdeath.html' , 'desc' => 'Another flash movie made in high school.' ),
	array ( 'name' => 'Jupiter' , 'link' => 'jupiter/index.htm' , 'desc' => 'Website about the planet jupiter.' ),
	array ( 'name' => 'Jupiter Geocities' , 'link' => 'jupiter/geocities/index.htm' , 'desc' => 'A web page related to the Jupiter site.' ),
	array ( 'name' => 'Table' , 'link' => 'jupiter/geocities/table.htm' , 'desc' => '?' ),
	array ( 'name' => 'Might and Magic' , 'link' => 'mandm/index.htm' , 'desc' => 'A fan page dedicated to Might and Magic.' ),
	array ( 'name' => 'Might and Magic Secrets' , 'link' => 'mandm/extras/secrets.htm' , 'desc' => 'Some hidden information that was on the Might and Magic site.' ),
	array ( 'name' => 'Moved' , 'link' => 'moved/index.htm' , 'desc' => '?' ),
	array ( 'name' => 'Other 1' , 'link' => 'otherweb/index.htm' , 'desc' => '?' ),
	array ( 'name' => 'Rating' , 'link' => 'otherweb/rating.htm' , 'desc' => 'Funny website about a rating board for websites.' ),
	array ( 'name' => 'Solution' , 'link' => 'solution/index.htm' , 'desc' => 'Solution to a puzzle.' ),
	array ( 'name' => 'Titanic' , 'link' => 'titanic/index.html' , 'desc' => 'A website dedicated to the film titanic, made as a high school project.' ),
);

printf( '<html><head><title>%s</title></head>' , $SiteTitle );
print( '<body>' );

printf( '<h1>%s</h1>' , $SiteTitle );

print( 'This is an archive of some of the stuff Beem Media has created over the years. Note that most of this was made when Beem Media founder Blaine Myers was 14 to 18 years old. Also expect that most links are broken or outdated. This is presented only as an interesting history.' );

print( '<ul>' );

foreach( $Sites as &$Item )
{
	printf( '<li><a href="%s">%s</a> - %s</li>' , $Item['link'] , $Item['name'] , $Item['desc'] );
}

print( '</ul>' );

printf( '<body>' );
printf( '</html>' );

?>