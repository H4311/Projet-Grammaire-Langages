<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="./html.dtd">

	<xsl:template match="rapport">
		<html>
			<body>
				<p>Hello World !</p>
			</body>
		</html>
		<xsl:for-each select="catalog/cd">
        <tr>
          <td><xsl:value-of select="title"/></td>
          <td><xsl:value-of select="artist"/></td>
        </tr>
      </xsl:for-each>
	</xsl:template>

</xsl:stylesheet> 
