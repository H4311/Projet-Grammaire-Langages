<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="./tests/html.dtd">

	<xsl:template match="rapport">
		<html>
			<body>
				<p>Hello World !</p>
			</body>
		</html>
	</xsl:template>
	
	<xsl:template match="img">
		<img>
			<xsl:attribute name="src">./@src</xsl:attribute>
			<xsl:attribute name="title">@title</xsl:attribute>
		</img>
	</xsl:template>

</xsl:stylesheet> 
