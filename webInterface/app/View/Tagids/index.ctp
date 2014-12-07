<div class="tagids index">
	<h2><?php echo __('Tagids'); ?></h2>
	<table cellpadding="0" cellspacing="0">
	<thead>
	<tr>
			<th><?php echo $this->Paginator->sort('id'); ?></th>
			<th><?php echo $this->Paginator->sort('tagid'); ?></th>
			<th><?php echo $this->Paginator->sort('created'); ?></th>
			<th><?php echo $this->Paginator->sort('modified'); ?></th>
			<th class="actions"><?php echo __('Actions'); ?></th>
	</tr>
	</thead>
	<tbody>
	<?php foreach ($tagids as $tagid): ?>
	<tr>
		<td><?php echo h($tagid['Tagid']['id']); ?>&nbsp;</td>
		<td><?php echo h($tagid['Tagid']['tagid']); ?>&nbsp;</td>
		<td><?php echo h($tagid['Tagid']['created']); ?>&nbsp;</td>
		<td><?php echo h($tagid['Tagid']['modified']); ?>&nbsp;</td>
		<td class="actions">
			<?php echo $this->Html->link(__('View'), array('action' => 'view', $tagid['Tagid']['id'])); ?>
			<?php echo $this->Html->link(__('Edit'), array('action' => 'edit', $tagid['Tagid']['id'])); ?>
			<?php echo $this->Form->postLink(__('Delete'), array('action' => 'delete', $tagid['Tagid']['id']), array(), __('Are you sure you want to delete # %s?', $tagid['Tagid']['id'])); ?>
		</td>
	</tr>
<?php endforeach; ?>
	</tbody>
	</table>
	<p>
	<?php
	echo $this->Paginator->counter(array(
	'format' => __('Page {:page} of {:pages}, showing {:current} records out of {:count} total, starting on record {:start}, ending on {:end}')
	));
	?>	</p>
	<div class="paging">
	<?php
		echo $this->Paginator->prev('< ' . __('previous'), array(), null, array('class' => 'prev disabled'));
		echo $this->Paginator->numbers(array('separator' => ''));
		echo $this->Paginator->next(__('next') . ' >', array(), null, array('class' => 'next disabled'));
	?>
	</div>
</div>
<div class="actions">
	<h3><?php echo __('Actions'); ?></h3>
	<ul>
		<li><?php echo $this->Html->link(__('Menu Principal'), array('controller' => 'pages' ,'action' => 'index')); ?></li>
		<li><?php echo $this->Html->link(__('Listar Usuários'), array('controller' => 'users', 'action' => 'index')); ?> </li>
		<li><?php echo $this->Html->link(__('Novo Usuário'), array('controller' => 'users', 'action' => 'add')); ?> </li>
	</ul>
</div>
s