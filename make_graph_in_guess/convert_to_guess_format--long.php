<?php

// reads an input file (of the hw7 assignment) and converts it to a format readable by GUESS Visualization: http://graphexploration.cond.org/

function getKey($node) {
	$ret = str_replace("-", "_", $node);
	$ret = str_replace(".", "_", $ret);
	return $ret;
}

if(isset($argv[1])) {
	$filename = $argv[1];
}
else {
	echo "Needs filename as parameter\n";
	exit;
}

$lines = file($filename);

$nodes = array();

foreach($lines as $line_num => $line) {
	if(0 === strpos($line, '#')) {
		continue;
	}
	$parts = explode("\t", trim($line));
	if('trip' == $parts[0]) {
		continue;
	}
	$nodes[$parts[0]] = $parts[0];
	$nodes[$parts[1]] = $parts[1];
	$nodes[$parts[0] . '__' . $parts[1]] = $parts[2];
}

// output the nodes
echo "nodedef> name,style,color,label\n";
foreach( $nodes as $key => $node ) {
	$color = 'yellow';
	$style = '6';
	$label = $node;
	if(strpos($key, '__') > 0) {
		$color = 'white';
		$style = '4';
		$label = $node;
	}
	echo getKey($key) . ',' . $style . ',' . $color . ',' . $label . "\n";
}

$edges = array();

// output the edges
echo "edgedef> node1,node2,color\n";
$color = 'black';
foreach( $nodes as $key => $node ) {
	if(strpos($key, '__') > 0) {
		$parts = explode("__", $key);
		echo getKey($key) . ',' . getKey($parts[0]) . ",$color\n";
		echo getKey($key) . ',' . getKey($parts[1]) . ",$color\n";
	}
}

