<div class="tagidsUsers form">
<?php echo $this->Form->create('TagidsUser'); ?>
	<fieldset>
		<legend><?php echo __('Edit Tagids User'); ?></legend>
	<?php
		echo $this->Form->input('id');
		echo $this->Form->input('tagid_id');
		echo $this->Form->input('user_id');
	?>
	</fieldset>
<?php echo $this->Form->end(__('Submit')); ?>
</div>
<div class="actions">
	<h3><?php echo __('Actions'); ?></h3>
	<ul>
		<li><?php echo $this->Html->link(__('Menu Principal'), array('controller' => 'pages' ,'action' => 'index')); ?></li>
		<li><?php echo $this->Form->postLink(__('Delete'), array('action' => 'delete', $this->Form->value('TagidsUser.id')), array(), __('Are you sure you want to delete # %s?', $this->Form->value('TagidsUser.id'))); ?></li>
		<li><?php echo $this->Html->link(__('List Usuários/Tag'), array('action' => 'index')); ?></li>
	</ul>
</div>
