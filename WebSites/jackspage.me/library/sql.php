<?php

$g_Sql = null;

function Sql_Init()
{
	global $g_Sql;
	
	@ $g_Sql = new mysqli(
		'localhost',
		'SQLUserName',
		'SQLPassword',
		'SQLDatabaseName');
	
	if(mysqli_connect_errno())
	{
		print('A problem occured while connecting to the database. Try again later.');
		echo( ' DB: '.$g_rcDBHost );
		$g_Sql = null;
		assert( false );
		return;
	}
}

function Sql_Deinit()
{
	global $g_Sql;
	assert('mysqli' == get_class($g_Sql));
	
	$g_Sql->close();

	$g_Sql = null;
}

function Sql_GetDb()
{
	global $g_Sql;
	assert('mysqli' == get_class($g_Sql));
	return $g_Sql;
}


function Sql_DoSelectQuery( $Table , $Items , $Where = null , $Order = null )
{
	$db = Sql_GetDb();
	
	$qry = 'select '.$Items.' from '.$Table;
	if( null != $Where )
	{
		$qry .= ' where '.$Where;
	}
	
	if( null != $Order )
	{
		$qry .= ' order by '.$Order;
	}
	
	
	$res = $db->query($qry);
	
	if(!$res)
	{
		print($qry."<br/>\n");
		printf("MySQL Querry Error: %s.<br/>\n", $db->error);
		assert( false );
		return;
	}
	
	$NumRows = $res->num_rows;
	for($i = 0; $i < $NumRows; $i++ )
	{
		$Rows[$i] = $res->fetch_assoc();
	}
	
	assert(count($Rows) == $NumRows );
	
	$res->free();
	
	return $Rows;
}

?>