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
}

// output the nodes
echo "nodedef> name,style,color,label\n";
foreach( $nodes as $node ) {
	echo getKey($node) . ',6,white,' . $node . "\n";
}

$edges = array();

// output the edges
echo "edgedef> node1,node2,color\n";
foreach($lines as $line_num => $line) {
	if(0 === strpos($line, '#')) {
		continue;
	}
	$parts = explode("\t", trim($line));
	if('trip' == $parts[0]) {
		continue;
	}
	$key = $parts[0] . '|' . $parts[1];
	if(isset($edges[$key])) {
		continue;
	}
	$key = $parts[1] . '|' . $parts[0];
	if(isset($edges[$key])) {
		continue;
	}
	$color = $parts[2];
	echo getKey($parts[ 0 ]) . ',' . getKey($parts[1]) . ",$color\n";
	$edges[$key] = $key;
	$key = $parts[0] . '|' . $parts[1];
	$edges[$key] = $key;
}
