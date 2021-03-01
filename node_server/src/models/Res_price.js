module.exports = (sequelize, type) => {
	return sequelize.define('Res_price',
	{
		ResPriceId: {
			type: type.INTEGER,
			primaryKey: true,
			autoIncrement: true
		},
		ResId: type.INTEGER,
		ResPriceValue: type.STRING
	},
	{
		tableName: 'tbl_dk_res_price',
		timestamps: false
	})
}